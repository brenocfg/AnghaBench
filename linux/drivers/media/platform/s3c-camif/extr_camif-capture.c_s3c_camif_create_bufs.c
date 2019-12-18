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
struct v4l2_create_buffers {int /*<<< orphan*/  count; } ;
struct file {int dummy; } ;
struct camif_vp {void* owner; int /*<<< orphan*/  vb_queue; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 
 int vb2_create_bufs (int /*<<< orphan*/ *,struct v4l2_create_buffers*) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_create_bufs(struct file *file, void *priv,
				 struct v4l2_create_buffers *create)
{
	struct camif_vp *vp = video_drvdata(file);
	int ret;

	if (vp->owner && vp->owner != priv)
		return -EBUSY;

	create->count = max_t(u32, 1, create->count);
	ret = vb2_create_bufs(&vp->vb_queue, create);

	if (!ret && vp->owner == NULL)
		vp->owner = priv;

	return ret;
}