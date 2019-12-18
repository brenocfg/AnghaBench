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
struct omap_dss_cpr_coefs {int /*<<< orphan*/  bb; int /*<<< orphan*/  bg; int /*<<< orphan*/  br; int /*<<< orphan*/  gb; int /*<<< orphan*/  gg; int /*<<< orphan*/  gr; int /*<<< orphan*/  rb; int /*<<< orphan*/  rg; int /*<<< orphan*/  rr; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CPR_COEF_B (int) ; 
 int /*<<< orphan*/  DISPC_CPR_COEF_G (int) ; 
 int /*<<< orphan*/  DISPC_CPR_COEF_R (int) ; 
 int FLD_VAL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dispc_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dss_mgr_is_lcd (int) ; 

__attribute__((used)) static void dispc_mgr_set_cpr_coef(enum omap_channel channel,
		const struct omap_dss_cpr_coefs *coefs)
{
	u32 coef_r, coef_g, coef_b;

	if (!dss_mgr_is_lcd(channel))
		return;

	coef_r = FLD_VAL(coefs->rr, 31, 22) | FLD_VAL(coefs->rg, 20, 11) |
		FLD_VAL(coefs->rb, 9, 0);
	coef_g = FLD_VAL(coefs->gr, 31, 22) | FLD_VAL(coefs->gg, 20, 11) |
		FLD_VAL(coefs->gb, 9, 0);
	coef_b = FLD_VAL(coefs->br, 31, 22) | FLD_VAL(coefs->bg, 20, 11) |
		FLD_VAL(coefs->bb, 9, 0);

	dispc_write_reg(DISPC_CPR_COEF_R(channel), coef_r);
	dispc_write_reg(DISPC_CPR_COEF_G(channel), coef_g);
	dispc_write_reg(DISPC_CPR_COEF_B(channel), coef_b);
}