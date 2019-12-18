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
struct omap_hdmi {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int hdmi_power_on_core (struct omap_hdmi*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi_core_enable(struct omap_hdmi *hdmi)
{
	int r = 0;

	DSSDBG("ENTER omapdss_hdmi_core_enable\n");

	mutex_lock(&hdmi->lock);

	r = hdmi_power_on_core(hdmi);
	if (r) {
		DSSERR("failed to power on device\n");
		goto err0;
	}

	mutex_unlock(&hdmi->lock);
	return 0;

err0:
	mutex_unlock(&hdmi->lock);
	return r;
}