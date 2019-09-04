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
struct v4l2_frequency_band {int dummy; } ;
struct snd_tea575x {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int snd_tea575x_enum_freq_bands (struct snd_tea575x*,struct v4l2_frequency_band*) ; 
 struct snd_tea575x* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_enum_freq_bands(struct file *file, void *priv,
					 struct v4l2_frequency_band *band)
{
	struct snd_tea575x *tea = video_drvdata(file);

	return snd_tea575x_enum_freq_bands(tea, band);
}