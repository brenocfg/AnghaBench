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
struct lmac {int lmac_type; int lane_to_sds; int /*<<< orphan*/  lmacid_bd; } ;
struct bgx {int lmac_count; struct lmac* lmac; int /*<<< orphan*/  bgx_id; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BGX_CMRX_CFG ; 
 int /*<<< orphan*/  BGX_CMR_BIST_STATUS ; 
 int /*<<< orphan*/  BGX_CMR_CHAN_MSK_AND ; 
 int /*<<< orphan*/  BGX_CMR_GLOBAL_CFG ; 
 scalar_t__ BGX_CMR_RX_DMACX_CAM ; 
 scalar_t__ BGX_CMR_RX_LMACS ; 
 scalar_t__ BGX_CMR_RX_STEERING ; 
 scalar_t__ BGX_CMR_TX_LMACS ; 
 unsigned long long CMR_GLOBAL_CFG_FCS_STRIP ; 
 unsigned long long MAX_BGX_CHANS_PER_LMAC ; 
 int RX_DMAC_COUNT ; 
 int RX_TRAFFIC_STEER_RULE_COUNT ; 
 int /*<<< orphan*/  bgx_reg_modify (struct bgx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ bgx_reg_read (struct bgx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_reg_write (struct bgx*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmac_count ; 

__attribute__((used)) static void bgx_init_hw(struct bgx *bgx)
{
	int i;
	struct lmac *lmac;

	bgx_reg_modify(bgx, 0, BGX_CMR_GLOBAL_CFG, CMR_GLOBAL_CFG_FCS_STRIP);
	if (bgx_reg_read(bgx, 0, BGX_CMR_BIST_STATUS))
		dev_err(&bgx->pdev->dev, "BGX%d BIST failed\n", bgx->bgx_id);

	/* Set lmac type and lane2serdes mapping */
	for (i = 0; i < bgx->lmac_count; i++) {
		lmac = &bgx->lmac[i];
		bgx_reg_write(bgx, i, BGX_CMRX_CFG,
			      (lmac->lmac_type << 8) | lmac->lane_to_sds);
		bgx->lmac[i].lmacid_bd = lmac_count;
		lmac_count++;
	}

	bgx_reg_write(bgx, 0, BGX_CMR_TX_LMACS, bgx->lmac_count);
	bgx_reg_write(bgx, 0, BGX_CMR_RX_LMACS, bgx->lmac_count);

	/* Set the backpressure AND mask */
	for (i = 0; i < bgx->lmac_count; i++)
		bgx_reg_modify(bgx, 0, BGX_CMR_CHAN_MSK_AND,
			       ((1ULL << MAX_BGX_CHANS_PER_LMAC) - 1) <<
			       (i * MAX_BGX_CHANS_PER_LMAC));

	/* Disable all MAC filtering */
	for (i = 0; i < RX_DMAC_COUNT; i++)
		bgx_reg_write(bgx, 0, BGX_CMR_RX_DMACX_CAM + (i * 8), 0x00);

	/* Disable MAC steering (NCSI traffic) */
	for (i = 0; i < RX_TRAFFIC_STEER_RULE_COUNT; i++)
		bgx_reg_write(bgx, 0, BGX_CMR_RX_STEERING + (i * 8), 0x00);
}