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
struct v4l2_tuner {int /*<<< orphan*/  index; } ;
struct v4l2_subdev {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct msi001_dev {struct spi_device* spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct msi001_dev* sd_to_msi001_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int msi001_s_tuner(struct v4l2_subdev *sd, const struct v4l2_tuner *v)
{
	struct msi001_dev *dev = sd_to_msi001_dev(sd);
	struct spi_device *spi = dev->spi;

	dev_dbg(&spi->dev, "index=%d\n", v->index);
	return 0;
}