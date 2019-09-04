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
struct v4l2_buffer {int dummy; } ;
struct file {int dummy; } ;
struct camif_vp {int /*<<< orphan*/  vb_queue; } ;

/* Variables and functions */
 int vb2_querybuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_querybuf(struct file *file, void *priv,
			      struct v4l2_buffer *buf)
{
	struct camif_vp *vp = video_drvdata(file);
	return vb2_querybuf(&vp->vb_queue, buf);
}