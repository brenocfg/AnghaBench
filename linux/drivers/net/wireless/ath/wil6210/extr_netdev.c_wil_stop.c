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
struct net_device {int dummy; } ;

/* Variables and functions */
 struct wil6210_priv* ndev_to_wil (struct net_device*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int wil_down (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_has_other_active_ifaces (struct wil6210_priv*,struct net_device*,int,int) ; 
 int /*<<< orphan*/  wil_pm_runtime_put (struct wil6210_priv*) ; 

__attribute__((used)) static int wil_stop(struct net_device *ndev)
{
	struct wil6210_priv *wil = ndev_to_wil(ndev);
	int rc = 0;

	wil_dbg_misc(wil, "stop\n");

	if (!wil_has_other_active_ifaces(wil, ndev, true, false)) {
		wil_dbg_misc(wil, "stop, last iface\n");
		rc = wil_down(wil);
		if (!rc)
			wil_pm_runtime_put(wil);
	}

	return rc;
}