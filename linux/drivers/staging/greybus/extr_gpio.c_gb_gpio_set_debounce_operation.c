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
typedef  int /*<<< orphan*/  u16 ;
struct gb_gpio_set_debounce_request {size_t which; int /*<<< orphan*/  usec; } ;
struct gb_gpio_controller {TYPE_1__* lines; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;
struct TYPE_2__ {int /*<<< orphan*/  debounce_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_GPIO_TYPE_SET_DEBOUNCE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_gpio_set_debounce_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_gpio_set_debounce_operation(struct gb_gpio_controller *ggc,
					  u8 which, u16 debounce_usec)
{
	struct gb_gpio_set_debounce_request request;
	int ret;

	request.which = which;
	request.usec = cpu_to_le16(debounce_usec);
	ret = gb_operation_sync(ggc->connection, GB_GPIO_TYPE_SET_DEBOUNCE,
				&request, sizeof(request), NULL, 0);
	if (!ret)
		ggc->lines[which].debounce_usec = debounce_usec;
	return ret;
}