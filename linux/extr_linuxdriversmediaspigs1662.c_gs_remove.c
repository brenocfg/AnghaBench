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
struct spi_device {int dummy; } ;

/* Variables and functions */
 struct v4l2_subdev* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int gs_remove(struct spi_device *spi)
{
	struct v4l2_subdev *sd = spi_get_drvdata(spi);

	v4l2_device_unregister_subdev(sd);

	return 0;
}