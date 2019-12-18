#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct v4l2_device {int dummy; } ;
struct spi_master {int dummy; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct spi_device {TYPE_2__ dev; } ;
struct spi_board_info {scalar_t__* modalias; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (scalar_t__*) ; 
 struct v4l2_subdev* spi_get_drvdata (struct spi_device*) ; 
 struct spi_device* spi_new_device (struct spi_master*,struct spi_board_info*) ; 
 int /*<<< orphan*/  spi_unregister_device (struct spi_device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_device_register_subdev (struct v4l2_device*,struct v4l2_subdev*) ; 

struct v4l2_subdev *v4l2_spi_new_subdev(struct v4l2_device *v4l2_dev,
					struct spi_master *master,
					struct spi_board_info *info)
{
	struct v4l2_subdev *sd = NULL;
	struct spi_device *spi = NULL;

	if (!v4l2_dev)
		return NULL;
	if (info->modalias[0])
		request_module(info->modalias);

	spi = spi_new_device(master, info);

	if (!spi || !spi->dev.driver)
		goto error;

	if (!try_module_get(spi->dev.driver->owner))
		goto error;

	sd = spi_get_drvdata(spi);

	/*
	 * Register with the v4l2_device which increases the module's
	 * use count as well.
	 */
	if (v4l2_device_register_subdev(v4l2_dev, sd))
		sd = NULL;

	/* Decrease the module use count to match the first try_module_get. */
	module_put(spi->dev.driver->owner);

error:
	/*
	 * If we have a client but no subdev, then something went wrong and
	 * we must unregister the client.
	 */
	if (!sd)
		spi_unregister_device(spi);

	return sd;
}