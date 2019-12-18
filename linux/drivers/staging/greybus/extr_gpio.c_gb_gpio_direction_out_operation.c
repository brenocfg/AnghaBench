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
struct gb_gpio_direction_out_request {size_t which; int value; } ;
struct gb_gpio_controller {TYPE_1__* lines; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;
struct TYPE_2__ {scalar_t__ direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_GPIO_TYPE_DIRECTION_OUT ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_gpio_direction_out_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_gpio_direction_out_operation(struct gb_gpio_controller *ggc,
					   u8 which, bool value_high)
{
	struct gb_gpio_direction_out_request request;
	int ret;

	request.which = which;
	request.value = value_high ? 1 : 0;
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_DIRECTION_OUT,
				&request, sizeof(request), NULL, 0);
	if (!ret)
		ggc->lines[which].direction = 0;
	return ret;
}