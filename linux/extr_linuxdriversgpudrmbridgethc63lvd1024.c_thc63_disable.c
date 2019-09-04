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
struct thc63_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  vcc; int /*<<< orphan*/  pdwn; int /*<<< orphan*/  oe; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 struct thc63_dev* to_thc63 (struct drm_bridge*) ; 

__attribute__((used)) static void thc63_disable(struct drm_bridge *bridge)
{
	struct thc63_dev *thc63 = to_thc63(bridge);
	int ret;

	gpiod_set_value(thc63->oe, 0);
	gpiod_set_value(thc63->pdwn, 1);

	ret = regulator_disable(thc63->vcc);
	if (ret)
		dev_err(thc63->dev,
			"Failed to disable regulator \"vcc\": %d\n", ret);
}