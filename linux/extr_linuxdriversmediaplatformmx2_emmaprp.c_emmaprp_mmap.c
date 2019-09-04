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
struct file {struct emmaprp_ctx* private_data; } ;
struct emmaprp_dev {int /*<<< orphan*/  dev_mutex; } ;
struct emmaprp_ctx {int /*<<< orphan*/  m2m_ctx; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int v4l2_m2m_mmap (struct file*,int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 struct emmaprp_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int emmaprp_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct emmaprp_dev *pcdev = video_drvdata(file);
	struct emmaprp_ctx *ctx = file->private_data;
	int ret;

	if (mutex_lock_interruptible(&pcdev->dev_mutex))
		return -ERESTARTSYS;
	ret = v4l2_m2m_mmap(file, ctx->m2m_ctx, vma);
	mutex_unlock(&pcdev->dev_mutex);
	return ret;
}