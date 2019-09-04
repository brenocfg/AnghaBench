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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct lmac {scalar_t__ lmac_type; int /*<<< orphan*/ * phydev; int /*<<< orphan*/  dmacs; int /*<<< orphan*/  is_sgmii; scalar_t__ check_link; int /*<<< orphan*/  dwork; } ;
struct bgx {struct lmac* lmac; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGX_CMRX_CFG ; 
 int /*<<< orphan*/  BGX_CMRX_RX_FIFO_LEN ; 
 int /*<<< orphan*/  BGX_CMRX_TX_FIFO_LEN ; 
 int /*<<< orphan*/  BGX_GMP_PCS_MRX_CTL ; 
 scalar_t__ BGX_MODE_10G_KR ; 
 scalar_t__ BGX_MODE_40G_KR ; 
 scalar_t__ BGX_MODE_XFI ; 
 scalar_t__ BGX_MODE_XLAUI ; 
 int /*<<< orphan*/  BGX_SPUX_CONTROL1 ; 
 int /*<<< orphan*/  CMR_EN ; 
 int /*<<< orphan*/  CMR_PKT_RX_EN ; 
 int /*<<< orphan*/  CMR_PKT_TX_EN ; 
 int /*<<< orphan*/  PCS_MRX_CTL_PWR_DN ; 
 int /*<<< orphan*/  SPU_CTL_LOW_POWER ; 
 int /*<<< orphan*/  bgx_flush_dmac_cam_filter (struct bgx*,size_t) ; 
 int /*<<< orphan*/  bgx_poll_reg (struct bgx*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bgx_reg_modify (struct bgx*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_reg_read (struct bgx*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_reg_write (struct bgx*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bgx_lmac_disable(struct bgx *bgx, u8 lmacid)
{
	struct lmac *lmac;
	u64 cfg;

	lmac = &bgx->lmac[lmacid];
	if (lmac->check_link) {
		/* Destroy work queue */
		cancel_delayed_work_sync(&lmac->dwork);
		destroy_workqueue(lmac->check_link);
	}

	/* Disable packet reception */
	cfg = bgx_reg_read(bgx, lmacid, BGX_CMRX_CFG);
	cfg &= ~CMR_PKT_RX_EN;
	bgx_reg_write(bgx, lmacid, BGX_CMRX_CFG, cfg);

	/* Give chance for Rx/Tx FIFO to get drained */
	bgx_poll_reg(bgx, lmacid, BGX_CMRX_RX_FIFO_LEN, (u64)0x1FFF, true);
	bgx_poll_reg(bgx, lmacid, BGX_CMRX_TX_FIFO_LEN, (u64)0x3FFF, true);

	/* Disable packet transmission */
	cfg = bgx_reg_read(bgx, lmacid, BGX_CMRX_CFG);
	cfg &= ~CMR_PKT_TX_EN;
	bgx_reg_write(bgx, lmacid, BGX_CMRX_CFG, cfg);

	/* Disable serdes lanes */
        if (!lmac->is_sgmii)
                bgx_reg_modify(bgx, lmacid,
                               BGX_SPUX_CONTROL1, SPU_CTL_LOW_POWER);
        else
                bgx_reg_modify(bgx, lmacid,
                               BGX_GMP_PCS_MRX_CTL, PCS_MRX_CTL_PWR_DN);

	/* Disable LMAC */
	cfg = bgx_reg_read(bgx, lmacid, BGX_CMRX_CFG);
	cfg &= ~CMR_EN;
	bgx_reg_write(bgx, lmacid, BGX_CMRX_CFG, cfg);

	bgx_flush_dmac_cam_filter(bgx, lmacid);
	kfree(lmac->dmacs);

	if ((lmac->lmac_type != BGX_MODE_XFI) &&
	    (lmac->lmac_type != BGX_MODE_XLAUI) &&
	    (lmac->lmac_type != BGX_MODE_40G_KR) &&
	    (lmac->lmac_type != BGX_MODE_10G_KR) && lmac->phydev)
		phy_disconnect(lmac->phydev);

	lmac->phydev = NULL;
}