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
struct TYPE_2__ {struct exynos_mic* driver_private; } ;
struct exynos_mic {TYPE_1__ bridge; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct exynos_mic* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int exynos_mic_bind(struct device *dev, struct device *master,
			   void *data)
{
	struct exynos_mic *mic = dev_get_drvdata(dev);

	mic->bridge.driver_private = mic;

	return 0;
}