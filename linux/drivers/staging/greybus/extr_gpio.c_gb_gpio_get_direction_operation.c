#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct gb_gpio_get_direction_response {int direction; } ;
struct gb_gpio_get_direction_request {int which; } ;
struct gb_gpio_controller {TYPE_1__* lines; int /*<<< orphan*/  connection; TYPE_2__* gbphy_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  request ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {int direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_GPIO_TYPE_GET_DIRECTION ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_gpio_get_direction_request*,int,struct gb_gpio_get_direction_response*,int) ; 

__attribute__((used)) static int gb_gpio_get_direction_operation(struct gb_gpio_controller *ggc,
					   u8 which)
{
	struct device *dev = &ggc->gbphy_dev->dev;
	struct gb_gpio_get_direction_request request;
	struct gb_gpio_get_direction_response response;
	int ret;
	u8 direction;

	request.which = which;
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_GET_DIRECTION,
				&request, sizeof(request),
				&response, sizeof(response));
	if (ret)
		return ret;

	direction = response.direction;
	if (direction && direction != 1) {
		dev_warn(dev, "gpio %u direction was %u (should be 0 or 1)\n",
			 which, direction);
	}
	ggc->lines[which].direction = direction ? 1 : 0;
	return 0;
}