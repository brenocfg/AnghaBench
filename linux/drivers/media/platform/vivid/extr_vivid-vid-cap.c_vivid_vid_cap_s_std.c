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
typedef  scalar_t__ v4l2_std_id ;
struct vivid_dev {scalar_t__* std_cap; size_t input; int /*<<< orphan*/  vb_vbi_cap_q; int /*<<< orphan*/  vb_vid_cap_q; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODATA ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_is_sdtv_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_update_format_cap (struct vivid_dev*,int) ; 

int vivid_vid_cap_s_std(struct file *file, void *priv, v4l2_std_id id)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (!vivid_is_sdtv_cap(dev))
		return -ENODATA;
	if (dev->std_cap[dev->input] == id)
		return 0;
	if (vb2_is_busy(&dev->vb_vid_cap_q) || vb2_is_busy(&dev->vb_vbi_cap_q))
		return -EBUSY;
	dev->std_cap[dev->input] = id;
	vivid_update_format_cap(dev, false);
	return 0;
}