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
struct ovl_priv_data {int enabling; scalar_t__ enabled; } ;
struct omap_overlay {int /*<<< orphan*/  id; TYPE_1__* manager; } ;
struct TYPE_2__ {int /*<<< orphan*/ * output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  apply_lock ; 
 int /*<<< orphan*/  data_lock ; 
 int /*<<< orphan*/  dss_apply_ovl_enable (struct omap_overlay*,int) ; 
 int dss_check_settings (TYPE_1__*) ; 
 int /*<<< orphan*/  dss_set_go_bits () ; 
 int /*<<< orphan*/  dss_setup_fifos () ; 
 int /*<<< orphan*/  dss_write_regs () ; 
 struct ovl_priv_data* get_ovl_priv (struct omap_overlay*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dss_ovl_enable(struct omap_overlay *ovl)
{
	struct ovl_priv_data *op = get_ovl_priv(ovl);
	unsigned long flags;
	int r;

	mutex_lock(&apply_lock);

	if (op->enabled) {
		r = 0;
		goto err1;
	}

	if (ovl->manager == NULL || ovl->manager->output == NULL) {
		r = -EINVAL;
		goto err1;
	}

	spin_lock_irqsave(&data_lock, flags);

	op->enabling = true;

	r = dss_check_settings(ovl->manager);
	if (r) {
		DSSERR("failed to enable overlay %d: check_settings failed\n",
				ovl->id);
		goto err2;
	}

	dss_setup_fifos();

	op->enabling = false;
	dss_apply_ovl_enable(ovl, true);

	dss_write_regs();
	dss_set_go_bits();

	spin_unlock_irqrestore(&data_lock, flags);

	mutex_unlock(&apply_lock);

	return 0;
err2:
	op->enabling = false;
	spin_unlock_irqrestore(&data_lock, flags);
err1:
	mutex_unlock(&apply_lock);
	return r;
}