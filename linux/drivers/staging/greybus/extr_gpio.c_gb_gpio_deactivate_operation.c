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
typedef  size_t u8 ;
struct device {int dummy; } ;
struct gbphy_device {struct device dev; } ;
struct gb_gpio_deactivate_request {size_t which; } ;
struct gb_gpio_controller {TYPE_1__* lines; int /*<<< orphan*/  connection; struct gbphy_device* gbphy_dev; } ;
typedef  int /*<<< orphan*/  request ;
struct TYPE_2__ {int active; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_GPIO_TYPE_DEACTIVATE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_gpio_deactivate_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbphy_runtime_put_autosuspend (struct gbphy_device*) ; 

__attribute__((used)) static void gb_gpio_deactivate_operation(struct gb_gpio_controller *ggc,
					 u8 which)
{
	struct gbphy_device *gbphy_dev = ggc->gbphy_dev;
	struct device *dev = &gbphy_dev->dev;
	struct gb_gpio_deactivate_request request;
	int ret;

	request.which = which;
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_DEACTIVATE,
				&request, sizeof(request), NULL, 0);
	if (ret) {
		dev_err(dev, "failed to deactivate gpio %u\n", which);
		goto out_pm_put;
	}

	ggc->lines[which].active = false;

out_pm_put:
	gbphy_runtime_put_autosuspend(gbphy_dev);
}