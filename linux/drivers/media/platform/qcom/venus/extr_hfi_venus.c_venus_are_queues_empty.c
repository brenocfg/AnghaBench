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
struct venus_hfi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFACEQ_CMD_IDX ; 
 int /*<<< orphan*/  IFACEQ_MSG_IDX ; 
 int venus_get_queue_size (struct venus_hfi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int venus_are_queues_empty(struct venus_hfi_device *hdev)
{
	int ret1, ret2;

	ret1 = venus_get_queue_size(hdev, IFACEQ_MSG_IDX);
	if (ret1 < 0)
		return ret1;

	ret2 = venus_get_queue_size(hdev, IFACEQ_CMD_IDX);
	if (ret2 < 0)
		return ret2;

	if (!ret1 && !ret2)
		return 1;

	return 0;
}