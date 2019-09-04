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
struct sirf_data {struct serdev_device* serdev; } ;
struct serdev_device {int /*<<< orphan*/  dev; } ;
struct gnss_device {int dummy; } ;

/* Variables and functions */
 struct sirf_data* gnss_get_drvdata (struct gnss_device*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_close (struct serdev_device*) ; 

__attribute__((used)) static void sirf_close(struct gnss_device *gdev)
{
	struct sirf_data *data = gnss_get_drvdata(gdev);
	struct serdev_device *serdev = data->serdev;

	serdev_device_close(serdev);

	pm_runtime_put(&serdev->dev);
}