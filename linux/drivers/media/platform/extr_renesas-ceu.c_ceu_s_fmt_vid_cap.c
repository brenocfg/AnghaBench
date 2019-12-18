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
struct v4l2_format {int dummy; } ;
struct file {int dummy; } ;
struct ceu_device {int /*<<< orphan*/  vb2_vq; } ;

/* Variables and functions */
 int EBUSY ; 
 int ceu_set_fmt (struct ceu_device*,struct v4l2_format*) ; 
 scalar_t__ vb2_is_streaming (int /*<<< orphan*/ *) ; 
 struct ceu_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int ceu_s_fmt_vid_cap(struct file *file, void *priv,
			     struct v4l2_format *f)
{
	struct ceu_device *ceudev = video_drvdata(file);

	if (vb2_is_streaming(&ceudev->vb2_vq))
		return -EBUSY;

	return ceu_set_fmt(ceudev, f);
}