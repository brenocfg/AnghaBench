#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ovl_priv_data {int /*<<< orphan*/  enabled; } ;
struct omap_overlay {TYPE_1__* manager; } ;
struct TYPE_2__ {int /*<<< orphan*/ * output; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  apply_lock ; 
 int /*<<< orphan*/  data_lock ; 
 int /*<<< orphan*/  dss_apply_ovl_enable (struct omap_overlay*,int) ; 
 int /*<<< orphan*/  dss_set_go_bits () ; 
 int /*<<< orphan*/  dss_write_regs () ; 
 struct ovl_priv_data* get_ovl_priv (struct omap_overlay*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dss_ovl_disable(struct omap_overlay *ovl)
{
	struct ovl_priv_data *op = get_ovl_priv(ovl);
	unsigned long flags;
	int r;

	mutex_lock(&apply_lock);

	if (!op->enabled) {
		r = 0;
		goto err;
	}

	if (ovl->manager == NULL || ovl->manager->output == NULL) {
		r = -EINVAL;
		goto err;
	}

	spin_lock_irqsave(&data_lock, flags);

	dss_apply_ovl_enable(ovl, false);
	dss_write_regs();
	dss_set_go_bits();

	spin_unlock_irqrestore(&data_lock, flags);

	mutex_unlock(&apply_lock);

	return 0;

err:
	mutex_unlock(&apply_lock);
	return r;
}