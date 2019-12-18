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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct dispc_device {int dummy; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_OVL_ACCU1 (int) ; 
 int /*<<< orphan*/  FEAT_REG_HORIZONTALACCU ; 
 int /*<<< orphan*/  FEAT_REG_VERTICALACCU ; 
 int FLD_VAL (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_get_reg_field (struct dispc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dispc_ovl_set_vid_accu1(struct dispc_device *dispc,
				    enum omap_plane_id plane, int haccu,
				    int vaccu)
{
	u32 val;
	u8 hor_start, hor_end, vert_start, vert_end;

	dispc_get_reg_field(dispc, FEAT_REG_HORIZONTALACCU,
			    &hor_start, &hor_end);
	dispc_get_reg_field(dispc, FEAT_REG_VERTICALACCU,
			    &vert_start, &vert_end);

	val = FLD_VAL(vaccu, vert_start, vert_end) |
			FLD_VAL(haccu, hor_start, hor_end);

	dispc_write_reg(dispc, DISPC_OVL_ACCU1(plane), val);
}