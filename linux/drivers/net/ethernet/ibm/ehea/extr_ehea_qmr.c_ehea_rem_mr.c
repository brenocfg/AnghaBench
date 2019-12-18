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
typedef  scalar_t__ u64 ;
struct ehea_mr {int /*<<< orphan*/  handle; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FORCE_FREE ; 
 scalar_t__ H_SUCCESS ; 
 scalar_t__ ehea_h_free_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int ehea_rem_mr(struct ehea_mr *mr)
{
	u64 hret;

	if (!mr || !mr->adapter)
		return -EINVAL;

	hret = ehea_h_free_resource(mr->adapter->handle, mr->handle,
				    FORCE_FREE);
	if (hret != H_SUCCESS) {
		pr_err("destroy MR failed\n");
		return -EIO;
	}

	return 0;
}