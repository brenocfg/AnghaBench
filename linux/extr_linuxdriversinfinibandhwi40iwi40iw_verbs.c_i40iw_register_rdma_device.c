#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * iwcm; int /*<<< orphan*/  dev; int /*<<< orphan*/  driver_id; } ;
struct i40iw_ib_device {TYPE_1__ ibdev; } ;
struct i40iw_device {struct i40iw_ib_device* iwibdev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RDMA_DRIVER_I40IW ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * i40iw_dev_attributes ; 
 struct i40iw_ib_device* i40iw_init_rdma_device (struct i40iw_device*) ; 
 int /*<<< orphan*/  ib_dealloc_device (TYPE_1__*) ; 
 int ib_register_device (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

int i40iw_register_rdma_device(struct i40iw_device *iwdev)
{
	int i, ret;
	struct i40iw_ib_device *iwibdev;

	iwdev->iwibdev = i40iw_init_rdma_device(iwdev);
	if (!iwdev->iwibdev)
		return -ENOMEM;
	iwibdev = iwdev->iwibdev;

	iwibdev->ibdev.driver_id = RDMA_DRIVER_I40IW;
	ret = ib_register_device(&iwibdev->ibdev, NULL);
	if (ret)
		goto error;

	for (i = 0; i < ARRAY_SIZE(i40iw_dev_attributes); ++i) {
		ret =
		    device_create_file(&iwibdev->ibdev.dev,
				       i40iw_dev_attributes[i]);
		if (ret) {
			while (i > 0) {
				i--;
				device_remove_file(&iwibdev->ibdev.dev, i40iw_dev_attributes[i]);
			}
			ib_unregister_device(&iwibdev->ibdev);
			goto error;
		}
	}
	return 0;
error:
	kfree(iwdev->iwibdev->ibdev.iwcm);
	iwdev->iwibdev->ibdev.iwcm = NULL;
	ib_dealloc_device(&iwdev->iwibdev->ibdev);
	return ret;
}