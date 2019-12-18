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
struct vivid_dev {scalar_t__ std_out; int /*<<< orphan*/  vb_vbi_out_q; int /*<<< orphan*/  vb_vid_out_q; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODATA ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_is_svid_out (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_update_format_out (struct vivid_dev*) ; 

int vivid_vid_out_s_std(struct file *file, void *priv, v4l2_std_id id)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (!vivid_is_svid_out(dev))
		return -ENODATA;
	if (dev->std_out == id)
		return 0;
	if (vb2_is_busy(&dev->vb_vid_out_q) || vb2_is_busy(&dev->vb_vbi_out_q))
		return -EBUSY;
	dev->std_out = id;
	vivid_update_format_out(dev);
	return 0;
}