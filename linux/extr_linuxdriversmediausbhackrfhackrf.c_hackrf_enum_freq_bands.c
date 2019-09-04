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
struct hackrf_dev {int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct v4l2_frequency_band*) ; 
 int EINVAL ; 
 struct v4l2_frequency_band* bands_adc_dac ; 
 struct v4l2_frequency_band* bands_rx_tx ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,size_t) ; 
 struct hackrf_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int hackrf_enum_freq_bands(struct file *file, void *priv,
		struct v4l2_frequency_band *band)
{
	struct hackrf_dev *dev = video_drvdata(file);
	int ret;

	dev_dbg(dev->dev, "tuner=%d type=%d index=%d\n",
			band->tuner, band->type, band->index);

	if (band->tuner == 0) {
		if (band->index >= ARRAY_SIZE(bands_adc_dac)) {
			ret = -EINVAL;
		} else {
			*band = bands_adc_dac[band->index];
			ret = 0;
		}
	} else if (band->tuner == 1) {
		if (band->index >= ARRAY_SIZE(bands_rx_tx)) {
			ret = -EINVAL;
		} else {
			*band = bands_rx_tx[band->index];
			ret = 0;
		}
	} else {
		ret = -EINVAL;
	}

	return ret;
}