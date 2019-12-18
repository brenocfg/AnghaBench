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
typedef  int u32 ;
struct panfrost_device {int /*<<< orphan*/  dev; scalar_t__ iomem; } ;

/* Variables and functions */
 scalar_t__ AS_STATUS (int) ; 
 int AS_STATUS_AS_ACTIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed_poll_timeout_atomic (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int wait_ready(struct panfrost_device *pfdev, u32 as_nr)
{
	int ret;
	u32 val;

	/* Wait for the MMU status to indicate there is no active command, in
	 * case one is pending. */
	ret = readl_relaxed_poll_timeout_atomic(pfdev->iomem + AS_STATUS(as_nr),
		val, !(val & AS_STATUS_AS_ACTIVE), 10, 1000);

	if (ret)
		dev_err(pfdev->dev, "AS_ACTIVE bit stuck\n");

	return ret;
}