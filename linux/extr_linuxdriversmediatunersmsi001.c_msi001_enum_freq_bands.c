#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct v4l2_frequency_band {size_t index; int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  capability; int /*<<< orphan*/  type; int /*<<< orphan*/  tuner; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct msi001_dev {struct spi_device* spi; } ;
struct TYPE_3__ {int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  capability; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* bands ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct msi001_dev* sd_to_msi001_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int msi001_enum_freq_bands(struct v4l2_subdev *sd,
				  struct v4l2_frequency_band *band)
{
	struct msi001_dev *dev = sd_to_msi001_dev(sd);
	struct spi_device *spi = dev->spi;

	dev_dbg(&spi->dev, "tuner=%d type=%d index=%d\n",
		band->tuner, band->type, band->index);

	if (band->index >= ARRAY_SIZE(bands))
		return -EINVAL;

	band->capability = bands[band->index].capability;
	band->rangelow = bands[band->index].rangelow;
	band->rangehigh = bands[band->index].rangehigh;

	return 0;
}