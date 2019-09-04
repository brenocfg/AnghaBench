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
struct sirf_data {int /*<<< orphan*/  speed; struct serdev_device* serdev; } ;
struct serdev_device {int /*<<< orphan*/  dev; } ;
struct gnss_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct sirf_data* gnss_get_drvdata (struct gnss_device*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_close (struct serdev_device*) ; 
 int serdev_device_open (struct serdev_device*) ; 
 int /*<<< orphan*/  serdev_device_set_baudrate (struct serdev_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdev_device_set_flow_control (struct serdev_device*,int) ; 

__attribute__((used)) static int sirf_open(struct gnss_device *gdev)
{
	struct sirf_data *data = gnss_get_drvdata(gdev);
	struct serdev_device *serdev = data->serdev;
	int ret;

	ret = serdev_device_open(serdev);
	if (ret)
		return ret;

	serdev_device_set_baudrate(serdev, data->speed);
	serdev_device_set_flow_control(serdev, false);

	ret = pm_runtime_get_sync(&serdev->dev);
	if (ret < 0) {
		dev_err(&gdev->dev, "failed to runtime resume: %d\n", ret);
		pm_runtime_put_noidle(&serdev->dev);
		goto err_close;
	}

	return 0;

err_close:
	serdev_device_close(serdev);

	return ret;
}