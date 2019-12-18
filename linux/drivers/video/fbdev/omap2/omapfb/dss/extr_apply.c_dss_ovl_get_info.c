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
struct ovl_priv_data {struct omap_overlay_info user_info; } ;
struct omap_overlay {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  data_lock ; 
 struct ovl_priv_data* get_ovl_priv (struct omap_overlay*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dss_ovl_get_info(struct omap_overlay *ovl,
		struct omap_overlay_info *info)
{
	struct ovl_priv_data *op = get_ovl_priv(ovl);
	unsigned long flags;

	spin_lock_irqsave(&data_lock, flags);

	*info = op->user_info;

	spin_unlock_irqrestore(&data_lock, flags);
}