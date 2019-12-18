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
struct ovl_priv_data {int user_info_dirty; int info_dirty; int /*<<< orphan*/  user_info; int /*<<< orphan*/  info; } ;
struct omap_overlay {int dummy; } ;

/* Variables and functions */
 struct ovl_priv_data* get_ovl_priv (struct omap_overlay*) ; 

__attribute__((used)) static void omap_dss_mgr_apply_ovl(struct omap_overlay *ovl)
{
	struct ovl_priv_data *op;

	op = get_ovl_priv(ovl);

	if (!op->user_info_dirty)
		return;

	op->user_info_dirty = false;
	op->info_dirty = true;
	op->info = op->user_info;
}