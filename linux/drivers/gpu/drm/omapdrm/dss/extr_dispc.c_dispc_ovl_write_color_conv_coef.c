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
struct csc_coef_yuv2rgb {int /*<<< orphan*/  full_range; int /*<<< orphan*/  bcb; int /*<<< orphan*/  by; int /*<<< orphan*/  bcr; int /*<<< orphan*/  gcr; int /*<<< orphan*/  gcb; int /*<<< orphan*/  rcb; int /*<<< orphan*/  gy; int /*<<< orphan*/  ry; int /*<<< orphan*/  rcr; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  CVAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  DISPC_OVL_CONV_COEF (int,int) ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dispc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_ovl_write_color_conv_coef(struct dispc_device *dispc,
					    enum omap_plane_id plane,
					    const struct csc_coef_yuv2rgb *ct)
{
#define CVAL(x, y) (FLD_VAL(x, 26, 16) | FLD_VAL(y, 10, 0))

	dispc_write_reg(dispc, DISPC_OVL_CONV_COEF(plane, 0), CVAL(ct->rcr, ct->ry));
	dispc_write_reg(dispc, DISPC_OVL_CONV_COEF(plane, 1), CVAL(ct->gy,  ct->rcb));
	dispc_write_reg(dispc, DISPC_OVL_CONV_COEF(plane, 2), CVAL(ct->gcb, ct->gcr));
	dispc_write_reg(dispc, DISPC_OVL_CONV_COEF(plane, 3), CVAL(ct->bcr, ct->by));
	dispc_write_reg(dispc, DISPC_OVL_CONV_COEF(plane, 4), CVAL(0, ct->bcb));

	REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(plane), ct->full_range, 11, 11);

#undef CVAL
}