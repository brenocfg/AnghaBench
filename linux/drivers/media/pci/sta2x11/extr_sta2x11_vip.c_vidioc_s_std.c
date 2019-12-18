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
typedef  int v4l2_std_id ;
struct sta2x11_vip {int std; int /*<<< orphan*/  decoder; int /*<<< orphan*/  format; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_ALL ; 
 int V4L2_STD_UNKNOWN ; 
 int /*<<< orphan*/ * formats_50 ; 
 int /*<<< orphan*/ * formats_60 ; 
 int /*<<< orphan*/  querystd ; 
 int /*<<< orphan*/  s_std ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  video ; 
 struct sta2x11_vip* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *priv, v4l2_std_id std)
{
	struct sta2x11_vip *vip = video_drvdata(file);

	/*
	 * This is here for backwards compatibility only.
	 * The use of V4L2_STD_ALL to trigger a querystd is non-standard.
	 */
	if (std == V4L2_STD_ALL) {
		v4l2_subdev_call(vip->decoder, video, querystd, &std);
		if (std == V4L2_STD_UNKNOWN)
			return -EIO;
	}

	if (vip->std != std) {
		vip->std = std;
		if (V4L2_STD_525_60 & std)
			vip->format = formats_60[0];
		else
			vip->format = formats_50[0];
	}

	return v4l2_subdev_call(vip->decoder, video, s_std, std);
}