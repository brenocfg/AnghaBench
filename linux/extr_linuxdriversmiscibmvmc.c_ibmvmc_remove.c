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
struct vio_dev {int /*<<< orphan*/  unit_address; int /*<<< orphan*/  dev; } ;
struct crq_server_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct crq_server_adapter* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvmc_release_crq_queue (struct crq_server_adapter*) ; 

__attribute__((used)) static int ibmvmc_remove(struct vio_dev *vdev)
{
	struct crq_server_adapter *adapter = dev_get_drvdata(&vdev->dev);

	dev_info(adapter->dev, "Entering remove for UA 0x%x\n",
		 vdev->unit_address);
	ibmvmc_release_crq_queue(adapter);

	return 0;
}