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
struct vm_area_struct {int dummy; } ;
struct file {scalar_t__ private_data; } ;
struct camif_vp {scalar_t__ owner; int /*<<< orphan*/  vb_queue; } ;

/* Variables and functions */
 int EBUSY ; 
 int vb2_mmap (int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct camif_vp *vp = video_drvdata(file);
	int ret;

	if (vp->owner && vp->owner != file->private_data)
		ret = -EBUSY;
	else
		ret = vb2_mmap(&vp->vb_queue, vma);

	return ret;
}