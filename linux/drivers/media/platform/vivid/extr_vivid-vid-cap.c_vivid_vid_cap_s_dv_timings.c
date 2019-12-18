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
struct vivid_dev {size_t input; struct v4l2_dv_timings* dv_timings_cap; int /*<<< orphan*/  vb_vid_cap_q; } ;
struct v4l2_dv_timings {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODATA ; 
 int /*<<< orphan*/  v4l2_find_dv_timings_cap (struct v4l2_dv_timings*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_match_dv_timings (struct v4l2_dv_timings*,struct v4l2_dv_timings*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  valid_cvt_gtf_timings (struct v4l2_dv_timings*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_dv_timings_cap ; 
 int /*<<< orphan*/  vivid_is_hdmi_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_update_format_cap (struct vivid_dev*,int) ; 

int vivid_vid_cap_s_dv_timings(struct file *file, void *_fh,
				    struct v4l2_dv_timings *timings)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (!vivid_is_hdmi_cap(dev))
		return -ENODATA;
	if (!v4l2_find_dv_timings_cap(timings, &vivid_dv_timings_cap,
				      0, NULL, NULL) &&
	    !valid_cvt_gtf_timings(timings))
		return -EINVAL;

	if (v4l2_match_dv_timings(timings, &dev->dv_timings_cap[dev->input],
				  0, false))
		return 0;
	if (vb2_is_busy(&dev->vb_vid_cap_q))
		return -EBUSY;

	dev->dv_timings_cap[dev->input] = *timings;
	vivid_update_format_cap(dev, false);
	return 0;
}