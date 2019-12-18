#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wbcir_data {scalar_t__* txbuf; int txstate; size_t txoff; size_t txlen; scalar_t__ sbase; } ;

/* Variables and functions */
 int WBCIR_IRQ_ERR ; 
 int WBCIR_IRQ_RX ; 
 int WBCIR_IRQ_TX_EMPTY ; 
 int WBCIR_IRQ_TX_LOW ; 
 scalar_t__ WBCIR_REG_SP3_ASCR ; 
 scalar_t__ WBCIR_REG_SP3_RXDATA ; 
 scalar_t__ WBCIR_REG_SP3_TXDATA ; 
#define  WBCIR_TXSTATE_ACTIVE 130 
#define  WBCIR_TXSTATE_ERROR 129 
#define  WBCIR_TXSTATE_INACTIVE 128 
 int WBCIR_TX_EOT ; 
 int WBCIR_TX_UNDERRUN ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outsb (scalar_t__,int*,unsigned int) ; 
 int /*<<< orphan*/  wbcir_set_irqmask (struct wbcir_data*,int) ; 

__attribute__((used)) static void
wbcir_irq_tx(struct wbcir_data *data)
{
	unsigned int space;
	unsigned int used;
	u8 bytes[16];
	u8 byte;

	if (!data->txbuf)
		return;

	switch (data->txstate) {
	case WBCIR_TXSTATE_INACTIVE:
		/* TX FIFO empty */
		space = 16;
		break;
	case WBCIR_TXSTATE_ACTIVE:
		/* TX FIFO low (3 bytes or less) */
		space = 13;
		break;
	case WBCIR_TXSTATE_ERROR:
		space = 0;
		break;
	default:
		return;
	}

	/*
	 * TX data is run-length coded in bytes: YXXXXXXX
	 * Y = space (1) or pulse (0)
	 * X = duration, encoded as (X + 1) * 10us (i.e 10 to 1280 us)
	 */
	for (used = 0; used < space && data->txoff != data->txlen; used++) {
		if (data->txbuf[data->txoff] == 0) {
			data->txoff++;
			continue;
		}
		byte = min((u32)0x80, data->txbuf[data->txoff]);
		data->txbuf[data->txoff] -= byte;
		byte--;
		byte |= (data->txoff % 2 ? 0x80 : 0x00); /* pulse/space */
		bytes[used] = byte;
	}

	while (data->txoff != data->txlen && data->txbuf[data->txoff] == 0)
		data->txoff++;

	if (used == 0) {
		/* Finished */
		if (data->txstate == WBCIR_TXSTATE_ERROR)
			/* Clear TX underrun bit */
			outb(WBCIR_TX_UNDERRUN, data->sbase + WBCIR_REG_SP3_ASCR);
		wbcir_set_irqmask(data, WBCIR_IRQ_RX | WBCIR_IRQ_ERR);
		kfree(data->txbuf);
		data->txbuf = NULL;
		data->txstate = WBCIR_TXSTATE_INACTIVE;
	} else if (data->txoff == data->txlen) {
		/* At the end of transmission, tell the hw before last byte */
		outsb(data->sbase + WBCIR_REG_SP3_TXDATA, bytes, used - 1);
		outb(WBCIR_TX_EOT, data->sbase + WBCIR_REG_SP3_ASCR);
		outb(bytes[used - 1], data->sbase + WBCIR_REG_SP3_TXDATA);
		wbcir_set_irqmask(data, WBCIR_IRQ_RX | WBCIR_IRQ_ERR |
				  WBCIR_IRQ_TX_EMPTY);
	} else {
		/* More data to follow... */
		outsb(data->sbase + WBCIR_REG_SP3_RXDATA, bytes, used);
		if (data->txstate == WBCIR_TXSTATE_INACTIVE) {
			wbcir_set_irqmask(data, WBCIR_IRQ_RX | WBCIR_IRQ_ERR |
					  WBCIR_IRQ_TX_LOW);
			data->txstate = WBCIR_TXSTATE_ACTIVE;
		}
	}
}