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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hdq_data {int /*<<< orphan*/  hdq_mutex; scalar_t__ hdq_usecount; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_w1_master ; 
 struct hdq_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w1_remove_master_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_hdq_remove(struct platform_device *pdev)
{
	struct hdq_data *hdq_data = platform_get_drvdata(pdev);

	mutex_lock(&hdq_data->hdq_mutex);

	if (hdq_data->hdq_usecount) {
		dev_dbg(&pdev->dev, "removed when use count is not zero\n");
		mutex_unlock(&hdq_data->hdq_mutex);
		return -EBUSY;
	}

	mutex_unlock(&hdq_data->hdq_mutex);

	/* remove module dependency */
	pm_runtime_disable(&pdev->dev);

	w1_remove_master_device(&omap_w1_master);

	return 0;
}