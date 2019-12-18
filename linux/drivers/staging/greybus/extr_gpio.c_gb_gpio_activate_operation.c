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
struct gbphy_device {int dummy; } ;
struct gb_gpio_controller {TYPE_1__* lines; int /*<<< orphan*/  connection; struct gbphy_device* gbphy_dev; } ;
struct gb_gpio_activate_request {size_t which; } ;
typedef  int /*<<< orphan*/  request ;
struct TYPE_2__ {int active; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_GPIO_TYPE_ACTIVATE ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_gpio_activate_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gbphy_runtime_get_sync (struct gbphy_device*) ; 
 int /*<<< orphan*/  gbphy_runtime_put_autosuspend (struct gbphy_device*) ; 

__attribute__((used)) static int gb_gpio_activate_operation(struct gb_gpio_controller *ggc, u8 which)
{
	struct gb_gpio_activate_request request;
	struct gbphy_device *gbphy_dev = ggc->gbphy_dev;
	int ret;

	ret = gbphy_runtime_get_sync(gbphy_dev);
	if (ret)
		return ret;

	request.which = which;
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_ACTIVATE,
				&request, sizeof(request), NULL, 0);
	if (ret) {
		gbphy_runtime_put_autosuspend(gbphy_dev);
		return ret;
	}

	ggc->lines[which].active = true;

	return 0;
}