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
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct camif_vp {int dummy; } ;

/* Variables and functions */
 int __camif_video_try_format (struct camif_vp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_vidioc_try_fmt(struct file *file, void *priv,
				    struct v4l2_format *f)
{
	struct camif_vp *vp = video_drvdata(file);
	return __camif_video_try_format(vp, &f->fmt.pix, NULL);
}