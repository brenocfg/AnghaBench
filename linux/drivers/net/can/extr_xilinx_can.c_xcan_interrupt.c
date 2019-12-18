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
typedef  int u32 ;
struct xcan_priv {int (* read_reg ) (struct xcan_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  napi; int /*<<< orphan*/  (* write_reg ) (struct xcan_priv*,int /*<<< orphan*/ ,int) ;} ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  XCAN_ICR_OFFSET ; 
 int /*<<< orphan*/  XCAN_IER_OFFSET ; 
 int /*<<< orphan*/  XCAN_ISR_OFFSET ; 
 int XCAN_IXR_ARBLST_MASK ; 
 int XCAN_IXR_BSOFF_MASK ; 
 int XCAN_IXR_ERROR_MASK ; 
 int XCAN_IXR_RXMNF_MASK ; 
 int XCAN_IXR_RXOFLW_MASK ; 
 int XCAN_IXR_SLP_MASK ; 
 int XCAN_IXR_TXOK_MASK ; 
 int XCAN_IXR_WKUP_MASK ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int stub4 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xcan_err_interrupt (struct net_device*,int) ; 
 int xcan_rx_int_mask (struct xcan_priv*) ; 
 int /*<<< orphan*/  xcan_state_interrupt (struct net_device*,int) ; 
 int /*<<< orphan*/  xcan_tx_interrupt (struct net_device*,int) ; 

__attribute__((used)) static irqreturn_t xcan_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = (struct net_device *)dev_id;
	struct xcan_priv *priv = netdev_priv(ndev);
	u32 isr, ier;
	u32 isr_errors;
	u32 rx_int_mask = xcan_rx_int_mask(priv);

	/* Get the interrupt status from Xilinx CAN */
	isr = priv->read_reg(priv, XCAN_ISR_OFFSET);
	if (!isr)
		return IRQ_NONE;

	/* Check for the type of interrupt and Processing it */
	if (isr & (XCAN_IXR_SLP_MASK | XCAN_IXR_WKUP_MASK)) {
		priv->write_reg(priv, XCAN_ICR_OFFSET, (XCAN_IXR_SLP_MASK |
				XCAN_IXR_WKUP_MASK));
		xcan_state_interrupt(ndev, isr);
	}

	/* Check for Tx interrupt and Processing it */
	if (isr & XCAN_IXR_TXOK_MASK)
		xcan_tx_interrupt(ndev, isr);

	/* Check for the type of error interrupt and Processing it */
	isr_errors = isr & (XCAN_IXR_ERROR_MASK | XCAN_IXR_RXOFLW_MASK |
			    XCAN_IXR_BSOFF_MASK | XCAN_IXR_ARBLST_MASK |
			    XCAN_IXR_RXMNF_MASK);
	if (isr_errors) {
		priv->write_reg(priv, XCAN_ICR_OFFSET, isr_errors);
		xcan_err_interrupt(ndev, isr);
	}

	/* Check for the type of receive interrupt and Processing it */
	if (isr & rx_int_mask) {
		ier = priv->read_reg(priv, XCAN_IER_OFFSET);
		ier &= ~rx_int_mask;
		priv->write_reg(priv, XCAN_IER_OFFSET, ier);
		napi_schedule(&priv->napi);
	}
	return IRQ_HANDLED;
}