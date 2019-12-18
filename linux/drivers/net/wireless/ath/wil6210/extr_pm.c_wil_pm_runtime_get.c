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
struct wil6210_priv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,int) ; 
 struct device* wil_to_dev (struct wil6210_priv*) ; 

int wil_pm_runtime_get(struct wil6210_priv *wil)
{
	int rc;
	struct device *dev = wil_to_dev(wil);

	rc = pm_runtime_get_sync(dev);
	if (rc < 0) {
		wil_err(wil, "pm_runtime_get_sync() failed, rc = %d\n", rc);
		pm_runtime_put_noidle(dev);
		return rc;
	}

	return 0;
}