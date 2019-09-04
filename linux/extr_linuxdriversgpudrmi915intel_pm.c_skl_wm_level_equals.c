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
struct skl_wm_level {scalar_t__ plane_en; scalar_t__ plane_res_l; scalar_t__ plane_res_b; } ;

/* Variables and functions */

bool skl_wm_level_equals(const struct skl_wm_level *l1,
			 const struct skl_wm_level *l2)
{
	if (l1->plane_en != l2->plane_en)
		return false;

	/* If both planes aren't enabled, the rest shouldn't matter */
	if (!l1->plane_en)
		return true;

	return (l1->plane_res_l == l2->plane_res_l &&
		l1->plane_res_b == l2->plane_res_b);
}