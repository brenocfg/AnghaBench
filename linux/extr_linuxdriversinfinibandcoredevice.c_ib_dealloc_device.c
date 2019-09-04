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
struct ib_device {scalar_t__ reg_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 scalar_t__ IB_DEV_UNINITIALIZED ; 
 scalar_t__ IB_DEV_UNREGISTERED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_restrack_clean (int /*<<< orphan*/ *) ; 

void ib_dealloc_device(struct ib_device *device)
{
	WARN_ON(device->reg_state != IB_DEV_UNREGISTERED &&
		device->reg_state != IB_DEV_UNINITIALIZED);
	rdma_restrack_clean(&device->res);
	put_device(&device->dev);
}