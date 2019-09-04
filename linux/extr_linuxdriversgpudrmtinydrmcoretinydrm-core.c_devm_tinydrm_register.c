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
struct tinydrm_device {TYPE_1__* drm; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int devm_add_action (struct device*,int /*<<< orphan*/ ,struct tinydrm_device*) ; 
 int /*<<< orphan*/  devm_tinydrm_register_release ; 
 int tinydrm_register (struct tinydrm_device*) ; 
 int /*<<< orphan*/  tinydrm_unregister (struct tinydrm_device*) ; 

int devm_tinydrm_register(struct tinydrm_device *tdev)
{
	struct device *dev = tdev->drm->dev;
	int ret;

	ret = tinydrm_register(tdev);
	if (ret)
		return ret;

	ret = devm_add_action(dev, devm_tinydrm_register_release, tdev);
	if (ret)
		tinydrm_unregister(tdev);

	return ret;
}