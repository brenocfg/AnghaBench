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
struct omap_overlay_info {int dummy; } ;
struct ovl_priv_data {int user_info_dirty; struct omap_overlay_info user_info; } ;
struct omap_overlay {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  data_lock ; 
 int dss_ovl_simple_check (struct omap_overlay*,struct omap_overlay_info*) ; 
 struct ovl_priv_data* get_ovl_priv (struct omap_overlay*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dss_ovl_set_info(struct omap_overlay *ovl,
		struct omap_overlay_info *info)
{
	struct ovl_priv_data *op = get_ovl_priv(ovl);
	unsigned long flags;
	int r;

	r = dss_ovl_simple_check(ovl, info);
	if (r)
		return r;

	spin_lock_irqsave(&data_lock, flags);

	op->user_info = *info;
	op->user_info_dirty = true;

	spin_unlock_irqrestore(&data_lock, flags);

	return 0;
}