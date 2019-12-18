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
struct panfrost_perfcnt {int /*<<< orphan*/  lock; struct panfrost_file_priv* user; } ;
struct panfrost_file_priv {struct panfrost_device* pfdev; } ;
struct panfrost_device {int /*<<< orphan*/  dev; struct panfrost_perfcnt* perfcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panfrost_perfcnt_disable_locked (struct panfrost_device*,struct panfrost_file_priv*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

void panfrost_perfcnt_close(struct panfrost_file_priv *pfile)
{
	struct panfrost_device *pfdev = pfile->pfdev;
	struct panfrost_perfcnt *perfcnt = pfdev->perfcnt;

	pm_runtime_get_sync(pfdev->dev);
	mutex_lock(&perfcnt->lock);
	if (perfcnt->user == pfile)
		panfrost_perfcnt_disable_locked(pfdev, pfile);
	mutex_unlock(&perfcnt->lock);
	pm_runtime_mark_last_busy(pfdev->dev);
	pm_runtime_put_autosuspend(pfdev->dev);
}