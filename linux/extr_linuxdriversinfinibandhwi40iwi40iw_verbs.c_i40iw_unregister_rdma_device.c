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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct i40iw_ib_device {TYPE_1__ ibdev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * i40iw_dev_attributes ; 
 int /*<<< orphan*/  ib_unregister_device (TYPE_1__*) ; 

__attribute__((used)) static void i40iw_unregister_rdma_device(struct i40iw_ib_device *iwibdev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(i40iw_dev_attributes); ++i)
		device_remove_file(&iwibdev->ibdev.dev,
				   i40iw_dev_attributes[i]);
	ib_unregister_device(&iwibdev->ibdev);
}