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
struct gsc_dev {int /*<<< orphan*/  lock; } ;
struct gsc_ctx {int /*<<< orphan*/  m2m_ctx; struct gsc_dev* gsc_dev; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 struct gsc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int v4l2_m2m_mmap (struct file*,int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int gsc_m2m_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct gsc_ctx *ctx = fh_to_ctx(file->private_data);
	struct gsc_dev *gsc = ctx->gsc_dev;
	int ret;

	if (mutex_lock_interruptible(&gsc->lock))
		return -ERESTARTSYS;

	ret = v4l2_m2m_mmap(file, ctx->m2m_ctx, vma);
	mutex_unlock(&gsc->lock);

	return ret;
}