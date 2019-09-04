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
struct vio_dev {scalar_t__ dev_no; int /*<<< orphan*/  type; } ;
struct vdc_check_port_data {scalar_t__ dev_no; int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 

__attribute__((used)) static int vdc_device_probed(struct device *dev, void *arg)
{
	struct vio_dev *vdev = to_vio_dev(dev);
	struct vdc_check_port_data *port_data;

	port_data = (struct vdc_check_port_data *)arg;

	if ((vdev->dev_no == port_data->dev_no) &&
	    (!(strcmp((char *)&vdev->type, port_data->type))) &&
		dev_get_drvdata(dev)) {
		/* This device has already been configured
		 * by vdc_port_probe()
		 */
		return 1;
	} else {
		return 0;
	}
}