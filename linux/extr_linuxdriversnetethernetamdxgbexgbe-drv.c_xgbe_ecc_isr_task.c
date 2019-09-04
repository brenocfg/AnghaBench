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
struct TYPE_3__ {int /*<<< orphan*/  (* disable_ecc_sec ) (struct xgbe_prv_data*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable_ecc_ded ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {TYPE_2__* vdata; TYPE_1__ hw_if; int /*<<< orphan*/  desc_sec_count; int /*<<< orphan*/  desc_sec_period; int /*<<< orphan*/  rx_sec_count; int /*<<< orphan*/  rx_sec_period; int /*<<< orphan*/  tx_sec_count; int /*<<< orphan*/  tx_sec_period; int /*<<< orphan*/  stopdev_work; int /*<<< orphan*/  desc_ded_count; int /*<<< orphan*/  desc_ded_period; int /*<<< orphan*/  rx_ded_count; int /*<<< orphan*/  rx_ded_period; int /*<<< orphan*/  tx_ded_count; int /*<<< orphan*/  tx_ded_period; int /*<<< orphan*/  netdev; } ;
struct TYPE_4__ {scalar_t__ irq_reissue_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_DED ; 
 int /*<<< orphan*/  DESC_SEC ; 
 int /*<<< orphan*/  RX_DED ; 
 int /*<<< orphan*/  RX_SEC ; 
 int /*<<< orphan*/  TX_DED ; 
 int /*<<< orphan*/  TX_SEC ; 
 int /*<<< orphan*/  XGBE_ECC_SEC_DESC ; 
 int /*<<< orphan*/  XGBE_ECC_SEC_RX ; 
 int /*<<< orphan*/  XGBE_ECC_SEC_TX ; 
 int /*<<< orphan*/  XP_ECC_IER ; 
 int /*<<< orphan*/  XP_ECC_ISR ; 
 scalar_t__ XP_GET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XP_INT_REISSUE_EN ; 
 unsigned int XP_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XP_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub2 (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int xgbe_ecc_ded (struct xgbe_prv_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ xgbe_ecc_sec (struct xgbe_prv_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void xgbe_ecc_isr_task(unsigned long data)
{
	struct xgbe_prv_data *pdata = (struct xgbe_prv_data *)data;
	unsigned int ecc_isr;
	bool stop = false;

	/* Mask status with only the interrupts we care about */
	ecc_isr = XP_IOREAD(pdata, XP_ECC_ISR);
	ecc_isr &= XP_IOREAD(pdata, XP_ECC_IER);
	netif_dbg(pdata, intr, pdata->netdev, "ECC_ISR=%#010x\n", ecc_isr);

	if (XP_GET_BITS(ecc_isr, XP_ECC_ISR, TX_DED)) {
		stop |= xgbe_ecc_ded(pdata, &pdata->tx_ded_period,
				     &pdata->tx_ded_count, "TX fifo");
	}

	if (XP_GET_BITS(ecc_isr, XP_ECC_ISR, RX_DED)) {
		stop |= xgbe_ecc_ded(pdata, &pdata->rx_ded_period,
				     &pdata->rx_ded_count, "RX fifo");
	}

	if (XP_GET_BITS(ecc_isr, XP_ECC_ISR, DESC_DED)) {
		stop |= xgbe_ecc_ded(pdata, &pdata->desc_ded_period,
				     &pdata->desc_ded_count,
				     "descriptor cache");
	}

	if (stop) {
		pdata->hw_if.disable_ecc_ded(pdata);
		schedule_work(&pdata->stopdev_work);
		goto out;
	}

	if (XP_GET_BITS(ecc_isr, XP_ECC_ISR, TX_SEC)) {
		if (xgbe_ecc_sec(pdata, &pdata->tx_sec_period,
				 &pdata->tx_sec_count, "TX fifo"))
			pdata->hw_if.disable_ecc_sec(pdata, XGBE_ECC_SEC_TX);
	}

	if (XP_GET_BITS(ecc_isr, XP_ECC_ISR, RX_SEC))
		if (xgbe_ecc_sec(pdata, &pdata->rx_sec_period,
				 &pdata->rx_sec_count, "RX fifo"))
			pdata->hw_if.disable_ecc_sec(pdata, XGBE_ECC_SEC_RX);

	if (XP_GET_BITS(ecc_isr, XP_ECC_ISR, DESC_SEC))
		if (xgbe_ecc_sec(pdata, &pdata->desc_sec_period,
				 &pdata->desc_sec_count, "descriptor cache"))
			pdata->hw_if.disable_ecc_sec(pdata, XGBE_ECC_SEC_DESC);

out:
	/* Clear all ECC interrupts */
	XP_IOWRITE(pdata, XP_ECC_ISR, ecc_isr);

	/* Reissue interrupt if status is not clear */
	if (pdata->vdata->irq_reissue_support)
		XP_IOWRITE(pdata, XP_INT_REISSUE_EN, 1 << 1);
}