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
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 struct device* wil_to_dev (struct wil6210_priv*) ; 

void wil_pm_runtime_put(struct wil6210_priv *wil)
{
	struct device *dev = wil_to_dev(wil);

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);
}