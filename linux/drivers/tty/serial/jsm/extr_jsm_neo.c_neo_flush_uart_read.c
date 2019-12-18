#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct jsm_channel {TYPE_1__* ch_bd; TYPE_2__* ch_neo_uart; } ;
struct TYPE_4__ {int /*<<< orphan*/  isr_fcr; } ;
struct TYPE_3__ {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_ENABLE_FIFO ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neo_flush_uart_read(struct jsm_channel *ch)
{
	u8 tmp = 0;
	int i = 0;

	if (!ch)
		return;

	writeb((UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_RCVR), &ch->ch_neo_uart->isr_fcr);

	for (i = 0; i < 10; i++) {

		/* Check to see if the UART feels it completely flushed the FIFO. */
		tmp = readb(&ch->ch_neo_uart->isr_fcr);
		if (tmp & 2) {
			jsm_dbg(IOCTL, &ch->ch_bd->pci_dev,
				"Still flushing RX UART... i: %d\n", i);
			udelay(10);
		}
		else
			break;
	}
}