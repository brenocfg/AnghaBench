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
struct gb_operation {int dummy; } ;
struct gb_control {int /*<<< orphan*/  dev; int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GB_CONTROL_TYPE_MODE_SWITCH ; 
 int /*<<< orphan*/  GB_OPERATION_FLAG_UNIDIRECTIONAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct gb_operation* gb_operation_create_core (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_operation_put (struct gb_operation*) ; 
 int gb_operation_request_send_sync (struct gb_operation*) ; 

int gb_control_mode_switch_operation(struct gb_control *control)
{
	struct gb_operation *operation;
	int ret;

	operation = gb_operation_create_core(control->connection,
					     GB_CONTROL_TYPE_MODE_SWITCH,
					     0, 0,
					     GB_OPERATION_FLAG_UNIDIRECTIONAL,
					     GFP_KERNEL);
	if (!operation)
		return -ENOMEM;

	ret = gb_operation_request_send_sync(operation);
	if (ret)
		dev_err(&control->dev, "failed to send mode switch: %d\n", ret);

	gb_operation_put(operation);

	return ret;
}