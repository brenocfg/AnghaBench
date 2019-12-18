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
struct omap_dss_device {scalar_t__ output_type; scalar_t__ type; struct omap_dss_device* src; struct omap_dss_device* dst; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_lock ; 

int omapdss_output_set_device(struct omap_dss_device *out,
		struct omap_dss_device *dssdev)
{
	int r;

	mutex_lock(&output_lock);

	if (out->dst) {
		DSSERR("output already has device %s connected to it\n",
			out->dst->name);
		r = -EINVAL;
		goto err;
	}

	if (out->output_type != dssdev->type) {
		DSSERR("output type and display type don't match\n");
		r = -EINVAL;
		goto err;
	}

	out->dst = dssdev;
	dssdev->src = out;

	mutex_unlock(&output_lock);

	return 0;
err:
	mutex_unlock(&output_lock);

	return r;
}