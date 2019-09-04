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
struct lmac {size_t lmacid; int use_training; int /*<<< orphan*/  lmac_type; } ;
struct bgx {size_t max_lmac; int lmac_count; struct lmac* lmac; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGX_CMR_RX_LMACS ; 
 int /*<<< orphan*/  BGX_MODE_INVALID ; 
 int /*<<< orphan*/  bgx_print_qlm_mode (struct bgx*,size_t) ; 
 int bgx_reg_read (struct bgx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_set_lmac_config (struct bgx*,size_t) ; 

__attribute__((used)) static void bgx_get_qlm_mode(struct bgx *bgx)
{
	struct lmac *lmac;
	u8  idx;

	/* Init all LMAC's type to invalid */
	for (idx = 0; idx < bgx->max_lmac; idx++) {
		lmac = &bgx->lmac[idx];
		lmac->lmacid = idx;
		lmac->lmac_type = BGX_MODE_INVALID;
		lmac->use_training = false;
	}

	/* It is assumed that low level firmware sets this value */
	bgx->lmac_count = bgx_reg_read(bgx, 0, BGX_CMR_RX_LMACS) & 0x7;
	if (bgx->lmac_count > bgx->max_lmac)
		bgx->lmac_count = bgx->max_lmac;

	for (idx = 0; idx < bgx->lmac_count; idx++) {
		bgx_set_lmac_config(bgx, idx);
		bgx_print_qlm_mode(bgx, idx);
	}
}