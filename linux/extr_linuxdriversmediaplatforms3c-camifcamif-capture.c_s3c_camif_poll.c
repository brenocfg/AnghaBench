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
struct poll_table_struct {int dummy; } ;
struct file {scalar_t__ private_data; } ;
struct camif_vp {scalar_t__ owner; int /*<<< orphan*/  vb_queue; struct camif_dev* camif; } ;
struct camif_dev {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLERR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_poll (int /*<<< orphan*/ *,struct file*,struct poll_table_struct*) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static __poll_t s3c_camif_poll(struct file *file,
				   struct poll_table_struct *wait)
{
	struct camif_vp *vp = video_drvdata(file);
	struct camif_dev *camif = vp->camif;
	__poll_t ret;

	mutex_lock(&camif->lock);
	if (vp->owner && vp->owner != file->private_data)
		ret = EPOLLERR;
	else
		ret = vb2_poll(&vp->vb_queue, file, wait);

	mutex_unlock(&camif->lock);
	return ret;
}