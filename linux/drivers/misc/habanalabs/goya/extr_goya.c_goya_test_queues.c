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
struct hl_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUMBER_OF_EXT_HW_QUEUES ; 
 int goya_test_queue (struct hl_device*,int) ; 

int goya_test_queues(struct hl_device *hdev)
{
	int i, rc, ret_val = 0;

	for (i = 0 ; i < NUMBER_OF_EXT_HW_QUEUES ; i++) {
		rc = goya_test_queue(hdev, i);
		if (rc)
			ret_val = -EINVAL;
	}

	return ret_val;
}