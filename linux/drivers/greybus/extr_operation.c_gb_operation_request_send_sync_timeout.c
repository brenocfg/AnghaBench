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
struct gb_operation {int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECANCELED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gb_operation_cancel (struct gb_operation*,int /*<<< orphan*/ ) ; 
 int gb_operation_request_send (struct gb_operation*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int gb_operation_result (struct gb_operation*) ; 
 int /*<<< orphan*/  gb_operation_sync_callback ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

int gb_operation_request_send_sync_timeout(struct gb_operation *operation,
					   unsigned int timeout)
{
	int ret;

	ret = gb_operation_request_send(operation, gb_operation_sync_callback,
					timeout, GFP_KERNEL);
	if (ret)
		return ret;

	ret = wait_for_completion_interruptible(&operation->completion);
	if (ret < 0) {
		/* Cancel the operation if interrupted */
		gb_operation_cancel(operation, -ECANCELED);
	}

	return gb_operation_result(operation);
}