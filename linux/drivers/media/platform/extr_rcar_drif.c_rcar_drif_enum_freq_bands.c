#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_frequency_band {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  subdev; } ;
struct rcar_drif_sdr {TYPE_1__ ep; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enum_freq_bands ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency_band*) ; 
 struct rcar_drif_sdr* video_drvdata (struct file*) ; 

__attribute__((used)) static int rcar_drif_enum_freq_bands(struct file *file, void *priv,
				     struct v4l2_frequency_band *band)
{
	struct rcar_drif_sdr *sdr = video_drvdata(file);

	return v4l2_subdev_call(sdr->ep.subdev, tuner, enum_freq_bands, band);
}