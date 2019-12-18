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
struct dispc_device {int dummy; } ;
struct csc_coef_rgb2yuv {int /*<<< orphan*/  full_range; int /*<<< orphan*/  cbb; int /*<<< orphan*/  cbr; int /*<<< orphan*/  cbg; int /*<<< orphan*/  crg; int /*<<< orphan*/  crb; int /*<<< orphan*/  yb; int /*<<< orphan*/  crr; int /*<<< orphan*/  yr; int /*<<< orphan*/  yg; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  CVAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int const) ; 
 int /*<<< orphan*/  DISPC_OVL_CONV_COEF (int const,int) ; 
 int OMAP_DSS_WB ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dispc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_wb_write_color_conv_coef(struct dispc_device *dispc,
					   const struct csc_coef_rgb2yuv *ct)
{
	const enum omap_plane_id plane = OMAP_DSS_WB;

#define CVAL(x, y) (FLD_VAL(x, 26, 16) | FLD_VAL(y, 10, 0))

	dispc_write_reg(dispc, DISPC_OVL_CONV_COEF(plane, 0), CVAL(ct->yg,  ct->yr));
	dispc_write_reg(dispc, DISPC_OVL_CONV_COEF(plane, 1), CVAL(ct->crr, ct->yb));
	dispc_write_reg(dispc, DISPC_OVL_CONV_COEF(plane, 2), CVAL(ct->crb, ct->crg));
	dispc_write_reg(dispc, DISPC_OVL_CONV_COEF(plane, 3), CVAL(ct->cbg, ct->cbr));
	dispc_write_reg(dispc, DISPC_OVL_CONV_COEF(plane, 4), CVAL(0, ct->cbb));

	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), ct->full_range, 11, 11);

#undef CVAL
}