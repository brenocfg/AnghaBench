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
typedef  int u64 ;
struct lmac {int lmac_type; size_t lane_to_sds; int /*<<< orphan*/  lmacid; } ;
struct bgx {scalar_t__ is_rgx; int /*<<< orphan*/  is_dlm; struct lmac* lmac; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGX_CMRX_CFG ; 
 int BGX_MODE_INVALID ; 
 int BGX_MODE_RGMII ; 
 int bgx_reg_read (struct bgx*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmac_set_lane2sds (struct bgx*,struct lmac*) ; 
 int /*<<< orphan*/  lmac_set_training (struct bgx*,struct lmac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bgx_set_lmac_config(struct bgx *bgx, u8 idx)
{
	struct lmac *lmac;
	u64 cmr_cfg;
	u8 lmac_type;
	u8 lane_to_sds;

	lmac = &bgx->lmac[idx];

	if (!bgx->is_dlm || bgx->is_rgx) {
		/* Read LMAC0 type to figure out QLM mode
		 * This is configured by low level firmware
		 */
		cmr_cfg = bgx_reg_read(bgx, 0, BGX_CMRX_CFG);
		lmac->lmac_type = (cmr_cfg >> 8) & 0x07;
		if (bgx->is_rgx)
			lmac->lmac_type = BGX_MODE_RGMII;
		lmac_set_training(bgx, lmac, 0);
		lmac_set_lane2sds(bgx, lmac);
		return;
	}

	/* For DLMs or SLMs on 80/81/83xx so many lane configurations
	 * are possible and vary across boards. Also Kernel doesn't have
	 * any way to identify board type/info and since firmware does,
	 * just take lmac type and serdes lane config as is.
	 */
	cmr_cfg = bgx_reg_read(bgx, idx, BGX_CMRX_CFG);
	lmac_type = (u8)((cmr_cfg >> 8) & 0x07);
	lane_to_sds = (u8)(cmr_cfg & 0xFF);
	/* Check if config is reset value */
	if ((lmac_type == 0) && (lane_to_sds == 0xE4))
		lmac->lmac_type = BGX_MODE_INVALID;
	else
		lmac->lmac_type = lmac_type;
	lmac->lane_to_sds = lane_to_sds;
	lmac_set_training(bgx, lmac, lmac->lmacid);
}