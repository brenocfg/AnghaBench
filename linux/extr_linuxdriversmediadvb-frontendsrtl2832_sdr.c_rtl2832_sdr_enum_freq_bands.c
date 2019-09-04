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
struct v4l2_frequency_band {int tuner; size_t index; int /*<<< orphan*/  type; } ;
struct rtl2832_sdr_dev {int /*<<< orphan*/  v4l2_subdev; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct v4l2_frequency_band*) ; 
 int EINVAL ; 
 scalar_t__ V4L2_SUBDEV_HAS_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_frequency_band* bands_adc ; 
 struct v4l2_frequency_band* bands_fm ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  enum_freq_bands ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency_band*) ; 
 struct rtl2832_sdr_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int rtl2832_sdr_enum_freq_bands(struct file *file, void *priv,
		struct v4l2_frequency_band *band)
{
	struct rtl2832_sdr_dev *dev = video_drvdata(file);
	struct platform_device *pdev = dev->pdev;
	int ret;

	dev_dbg(&pdev->dev, "tuner=%d type=%d index=%d\n",
		band->tuner, band->type, band->index);

	if (band->tuner == 0) {
		if (band->index >= ARRAY_SIZE(bands_adc))
			return -EINVAL;

		*band = bands_adc[band->index];
		ret = 0;
	} else if (band->tuner == 1 &&
		   V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, tuner, enum_freq_bands)) {
		ret = v4l2_subdev_call(dev->v4l2_subdev, tuner, enum_freq_bands, band);
	} else if (band->tuner == 1) {
		if (band->index >= ARRAY_SIZE(bands_fm))
			return -EINVAL;

		*band = bands_fm[band->index];
		ret = 0;
	} else {
		ret = -EINVAL;
	}
	return ret;
}