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
struct v4l2_fh {int /*<<< orphan*/  m2m_ctx; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int v4l2_m2m_mmap (struct file*,int /*<<< orphan*/ ,struct vm_area_struct*) ; 

int v4l2_m2m_fop_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct v4l2_fh *fh = file->private_data;

	return v4l2_m2m_mmap(file, fh->m2m_ctx, vma);
}