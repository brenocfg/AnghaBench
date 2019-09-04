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
struct exynos_mic {int /*<<< orphan*/  dev; int /*<<< orphan*/  enabled; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct exynos_mic* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mic_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_mic_unbind(struct device *dev, struct device *master,
			      void *data)
{
	struct exynos_mic *mic = dev_get_drvdata(dev);

	mutex_lock(&mic_mutex);
	if (!mic->enabled)
		goto already_disabled;

	pm_runtime_put(mic->dev);

already_disabled:
	mutex_unlock(&mic_mutex);
}