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
struct v4l2_frequency_band {scalar_t__ tuner; size_t index; } ;
struct radio_tea5777 {int /*<<< orphan*/  has_am; } ;
struct file {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct v4l2_frequency_band*) ; 
 size_t BAND_AM ; 
 int EINVAL ; 
 struct v4l2_frequency_band* bands ; 
 struct radio_tea5777* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_enum_freq_bands(struct file *file, void *priv,
					 struct v4l2_frequency_band *band)
{
	struct radio_tea5777 *tea = video_drvdata(file);

	if (band->tuner != 0 || band->index >= ARRAY_SIZE(bands) ||
	    (!tea->has_am && band->index == BAND_AM))
		return -EINVAL;

	*band = bands[band->index];
	return 0;
}