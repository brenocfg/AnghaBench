#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct lmac {int lmacid; scalar_t__ lmac_type; scalar_t__ use_training; } ;
struct bgx {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BCK_EN ; 
 int /*<<< orphan*/  BGX_CMRX_CFG ; 
 scalar_t__ BGX_MODE_10G_KR ; 
 scalar_t__ BGX_MODE_40G_KR ; 
 scalar_t__ BGX_MODE_RXAUI ; 
 int /*<<< orphan*/  BGX_SMUX_CBFC_CTL ; 
 int /*<<< orphan*/  BGX_SMUX_RX_INT ; 
 int /*<<< orphan*/  BGX_SMUX_RX_JABBER ; 
 int /*<<< orphan*/  BGX_SMUX_TX_APPEND ; 
 int /*<<< orphan*/  BGX_SMUX_TX_CTL ; 
 int /*<<< orphan*/  BGX_SMUX_TX_INT ; 
 int /*<<< orphan*/  BGX_SMUX_TX_PAUSE_PKT_INTERVAL ; 
 int /*<<< orphan*/  BGX_SMUX_TX_PAUSE_PKT_TIME ; 
 int /*<<< orphan*/  BGX_SMUX_TX_PAUSE_ZERO ; 
 int /*<<< orphan*/  BGX_SMUX_TX_THRESH ; 
 int /*<<< orphan*/  BGX_SPUX_AN_ADV ; 
 int /*<<< orphan*/  BGX_SPUX_AN_CONTROL ; 
 int /*<<< orphan*/  BGX_SPUX_BR_PMD_CRTL ; 
 int /*<<< orphan*/  BGX_SPUX_BR_PMD_LD_CUP ; 
 int /*<<< orphan*/  BGX_SPUX_BR_PMD_LD_REP ; 
 int /*<<< orphan*/  BGX_SPUX_BR_PMD_LP_CUP ; 
 int /*<<< orphan*/  BGX_SPUX_CONTROL1 ; 
 int /*<<< orphan*/  BGX_SPUX_FEC_CONTROL ; 
 int /*<<< orphan*/  BGX_SPUX_INT ; 
 int /*<<< orphan*/  BGX_SPUX_MISC_CONTROL ; 
 int /*<<< orphan*/  BGX_SPU_DBG_CONTROL ; 
 int CMR_EN ; 
 int DEFAULT_PAUSE_TIME ; 
 int DRP_EN ; 
 int MAX_FRAME_SIZE ; 
 int RX_EN ; 
 int SMU_TX_APPEND_FCS_D ; 
 int SMU_TX_CTL_DIC_EN ; 
 int SMU_TX_CTL_UNI_EN ; 
 int SPU_AN_CTL_AN_EN ; 
 int SPU_AN_CTL_XNP_EN ; 
 int SPU_CTL_LOW_POWER ; 
 int SPU_CTL_RESET ; 
 int SPU_DBG_CTL_AN_ARB_LINK_CHK_EN ; 
 int SPU_FEC_CTL_FEC_EN ; 
 int SPU_MISC_CTL_INTLV_RDISP ; 
 int SPU_MISC_CTL_RX_DIS ; 
 int SPU_PMD_CRTL_TRAIN_EN ; 
 int TX_EN ; 
 scalar_t__ bgx_poll_reg (struct bgx*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bgx_reg_modify (struct bgx*,int,int /*<<< orphan*/ ,int) ; 
 int bgx_reg_read (struct bgx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_reg_write (struct bgx*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int bgx_lmac_xaui_init(struct bgx *bgx, struct lmac *lmac)
{
	u64 cfg;
	int lmacid = lmac->lmacid;

	/* Reset SPU */
	bgx_reg_modify(bgx, lmacid, BGX_SPUX_CONTROL1, SPU_CTL_RESET);
	if (bgx_poll_reg(bgx, lmacid, BGX_SPUX_CONTROL1, SPU_CTL_RESET, true)) {
		dev_err(&bgx->pdev->dev, "BGX SPU reset not completed\n");
		return -1;
	}

	/* Disable LMAC */
	cfg = bgx_reg_read(bgx, lmacid, BGX_CMRX_CFG);
	cfg &= ~CMR_EN;
	bgx_reg_write(bgx, lmacid, BGX_CMRX_CFG, cfg);

	bgx_reg_modify(bgx, lmacid, BGX_SPUX_CONTROL1, SPU_CTL_LOW_POWER);
	/* Set interleaved running disparity for RXAUI */
	if (lmac->lmac_type == BGX_MODE_RXAUI)
		bgx_reg_modify(bgx, lmacid, BGX_SPUX_MISC_CONTROL,
			       SPU_MISC_CTL_INTLV_RDISP);

	/* Clear receive packet disable */
	cfg = bgx_reg_read(bgx, lmacid, BGX_SPUX_MISC_CONTROL);
	cfg &= ~SPU_MISC_CTL_RX_DIS;
	bgx_reg_write(bgx, lmacid, BGX_SPUX_MISC_CONTROL, cfg);

	/* clear all interrupts */
	cfg = bgx_reg_read(bgx, lmacid, BGX_SMUX_RX_INT);
	bgx_reg_write(bgx, lmacid, BGX_SMUX_RX_INT, cfg);
	cfg = bgx_reg_read(bgx, lmacid, BGX_SMUX_TX_INT);
	bgx_reg_write(bgx, lmacid, BGX_SMUX_TX_INT, cfg);
	cfg = bgx_reg_read(bgx, lmacid, BGX_SPUX_INT);
	bgx_reg_write(bgx, lmacid, BGX_SPUX_INT, cfg);

	if (lmac->use_training) {
		bgx_reg_write(bgx, lmacid, BGX_SPUX_BR_PMD_LP_CUP, 0x00);
		bgx_reg_write(bgx, lmacid, BGX_SPUX_BR_PMD_LD_CUP, 0x00);
		bgx_reg_write(bgx, lmacid, BGX_SPUX_BR_PMD_LD_REP, 0x00);
		/* training enable */
		bgx_reg_modify(bgx, lmacid,
			       BGX_SPUX_BR_PMD_CRTL, SPU_PMD_CRTL_TRAIN_EN);
	}

	/* Append FCS to each packet */
	bgx_reg_modify(bgx, lmacid, BGX_SMUX_TX_APPEND, SMU_TX_APPEND_FCS_D);

	/* Disable forward error correction */
	cfg = bgx_reg_read(bgx, lmacid, BGX_SPUX_FEC_CONTROL);
	cfg &= ~SPU_FEC_CTL_FEC_EN;
	bgx_reg_write(bgx, lmacid, BGX_SPUX_FEC_CONTROL, cfg);

	/* Disable autoneg */
	cfg = bgx_reg_read(bgx, lmacid, BGX_SPUX_AN_CONTROL);
	cfg = cfg & ~(SPU_AN_CTL_AN_EN | SPU_AN_CTL_XNP_EN);
	bgx_reg_write(bgx, lmacid, BGX_SPUX_AN_CONTROL, cfg);

	cfg = bgx_reg_read(bgx, lmacid, BGX_SPUX_AN_ADV);
	if (lmac->lmac_type == BGX_MODE_10G_KR)
		cfg |= (1 << 23);
	else if (lmac->lmac_type == BGX_MODE_40G_KR)
		cfg |= (1 << 24);
	else
		cfg &= ~((1 << 23) | (1 << 24));
	cfg = cfg & (~((1ULL << 25) | (1ULL << 22) | (1ULL << 12)));
	bgx_reg_write(bgx, lmacid, BGX_SPUX_AN_ADV, cfg);

	cfg = bgx_reg_read(bgx, 0, BGX_SPU_DBG_CONTROL);
	cfg &= ~SPU_DBG_CTL_AN_ARB_LINK_CHK_EN;
	bgx_reg_write(bgx, 0, BGX_SPU_DBG_CONTROL, cfg);

	/* Enable lmac */
	bgx_reg_modify(bgx, lmacid, BGX_CMRX_CFG, CMR_EN);

	cfg = bgx_reg_read(bgx, lmacid, BGX_SPUX_CONTROL1);
	cfg &= ~SPU_CTL_LOW_POWER;
	bgx_reg_write(bgx, lmacid, BGX_SPUX_CONTROL1, cfg);

	cfg = bgx_reg_read(bgx, lmacid, BGX_SMUX_TX_CTL);
	cfg &= ~SMU_TX_CTL_UNI_EN;
	cfg |= SMU_TX_CTL_DIC_EN;
	bgx_reg_write(bgx, lmacid, BGX_SMUX_TX_CTL, cfg);

	/* Enable receive and transmission of pause frames */
	bgx_reg_write(bgx, lmacid, BGX_SMUX_CBFC_CTL, ((0xffffULL << 32) |
		      BCK_EN | DRP_EN | TX_EN | RX_EN));
	/* Configure pause time and interval */
	bgx_reg_write(bgx, lmacid,
		      BGX_SMUX_TX_PAUSE_PKT_TIME, DEFAULT_PAUSE_TIME);
	cfg = bgx_reg_read(bgx, lmacid, BGX_SMUX_TX_PAUSE_PKT_INTERVAL);
	cfg &= ~0xFFFFull;
	bgx_reg_write(bgx, lmacid, BGX_SMUX_TX_PAUSE_PKT_INTERVAL,
		      cfg | (DEFAULT_PAUSE_TIME - 0x1000));
	bgx_reg_write(bgx, lmacid, BGX_SMUX_TX_PAUSE_ZERO, 0x01);

	/* take lmac_count into account */
	bgx_reg_modify(bgx, lmacid, BGX_SMUX_TX_THRESH, (0x100 - 1));
	/* max packet size */
	bgx_reg_modify(bgx, lmacid, BGX_SMUX_RX_JABBER, MAX_FRAME_SIZE);

	return 0;
}