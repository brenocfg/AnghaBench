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
struct v4l2_subdev {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct msi001_dev {int /*<<< orphan*/  hdl; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct msi001_dev*) ; 
 struct msi001_dev* sd_to_msi001_dev (struct v4l2_subdev*) ; 
 struct v4l2_subdev* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msi001_remove(struct spi_device *spi)
{
	struct v4l2_subdev *sd = spi_get_drvdata(spi);
	struct msi001_dev *dev = sd_to_msi001_dev(sd);

	dev_dbg(&spi->dev, "\n");

	/*
	 * Registered by v4l2_spi_new_subdev() from master driver, but we must
	 * unregister it from here. Weird.
	 */
	v4l2_device_unregister_subdev(&dev->sd);
	v4l2_ctrl_handler_free(&dev->hdl);
	kfree(dev);
	return 0;
}