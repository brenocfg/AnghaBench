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
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  tuner; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct msi001_dev {int /*<<< orphan*/  f_tuner; struct spi_device* spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct msi001_dev* sd_to_msi001_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int msi001_g_frequency(struct v4l2_subdev *sd, struct v4l2_frequency *f)
{
	struct msi001_dev *dev = sd_to_msi001_dev(sd);
	struct spi_device *spi = dev->spi;

	dev_dbg(&spi->dev, "tuner=%d\n", f->tuner);
	f->frequency = dev->f_tuner;
	return 0;
}