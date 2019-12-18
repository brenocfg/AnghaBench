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

/* Variables and functions */
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  FEAT_ALPHA_FREE_ZORDER ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dispc_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int dispc_get_num_ovls (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_ovl_enable_zorder_planes(struct dispc_device *dispc)
{
	int i;

	if (!dispc_has_feature(dispc, FEAT_ALPHA_FREE_ZORDER))
		return;

	for (i = 0; i < dispc_get_num_ovls(dispc); i++)
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES(i), 1, 25, 25);
}