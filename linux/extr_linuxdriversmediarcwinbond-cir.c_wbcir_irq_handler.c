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
struct wbcir_data {int irqmask; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  txstate; scalar_t__ sbase; int /*<<< orphan*/  dev; int /*<<< orphan*/  rxstate; } ;
struct pnp_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  WBCIR_BANK_0 ; 
 int WBCIR_IRQ_ERR ; 
 int WBCIR_IRQ_RX ; 
 int WBCIR_IRQ_TX_EMPTY ; 
 int WBCIR_IRQ_TX_LOW ; 
 scalar_t__ WBCIR_REG_SP3_ASCR ; 
 scalar_t__ WBCIR_REG_SP3_EIR ; 
 scalar_t__ WBCIR_REG_SP3_LSR ; 
 int /*<<< orphan*/  WBCIR_RXSTATE_ERROR ; 
 int WBCIR_RX_OVERRUN ; 
 int /*<<< orphan*/  WBCIR_TXSTATE_ERROR ; 
 int WBCIR_TX_UNDERRUN ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  ir_raw_event_reset (int /*<<< orphan*/ ) ; 
 struct wbcir_data* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wbcir_irq_rx (struct wbcir_data*,struct pnp_dev*) ; 
 int /*<<< orphan*/  wbcir_irq_tx (struct wbcir_data*) ; 
 int /*<<< orphan*/  wbcir_select_bank (struct wbcir_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
wbcir_irq_handler(int irqno, void *cookie)
{
	struct pnp_dev *device = cookie;
	struct wbcir_data *data = pnp_get_drvdata(device);
	unsigned long flags;
	u8 status;

	spin_lock_irqsave(&data->spinlock, flags);
	wbcir_select_bank(data, WBCIR_BANK_0);
	status = inb(data->sbase + WBCIR_REG_SP3_EIR);
	status &= data->irqmask;

	if (!status) {
		spin_unlock_irqrestore(&data->spinlock, flags);
		return IRQ_NONE;
	}

	if (status & WBCIR_IRQ_ERR) {
		/* RX overflow? (read clears bit) */
		if (inb(data->sbase + WBCIR_REG_SP3_LSR) & WBCIR_RX_OVERRUN) {
			data->rxstate = WBCIR_RXSTATE_ERROR;
			ir_raw_event_reset(data->dev);
		}

		/* TX underflow? */
		if (inb(data->sbase + WBCIR_REG_SP3_ASCR) & WBCIR_TX_UNDERRUN)
			data->txstate = WBCIR_TXSTATE_ERROR;
	}

	if (status & WBCIR_IRQ_RX)
		wbcir_irq_rx(data, device);

	if (status & (WBCIR_IRQ_TX_LOW | WBCIR_IRQ_TX_EMPTY))
		wbcir_irq_tx(data);

	spin_unlock_irqrestore(&data->spinlock, flags);
	return IRQ_HANDLED;
}