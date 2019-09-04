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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct vio_dev {TYPE_1__ dev; int /*<<< orphan*/  type; int /*<<< orphan*/  dev_no; } ;
struct vdc_check_port_data {char* type; int /*<<< orphan*/  dev_no; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* device_find_child (int /*<<< orphan*/ ,struct vdc_check_port_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdc_device_probed ; 

__attribute__((used)) static bool vdc_port_mpgroup_check(struct vio_dev *vdev)
{
	struct vdc_check_port_data port_data;
	struct device *dev;

	port_data.dev_no = vdev->dev_no;
	port_data.type = (char *)&vdev->type;

	dev = device_find_child(vdev->dev.parent, &port_data,
				vdc_device_probed);

	if (dev)
		return true;

	return false;
}