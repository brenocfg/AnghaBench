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
struct vm_area_struct {unsigned long vm_pgoff; } ;
struct s5p_mfc_ctx {int /*<<< orphan*/  vq_dst; int /*<<< orphan*/  vq_src; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 unsigned long DST_QUEUE_OFF_BASE ; 
 unsigned long PAGE_SHIFT ; 
 struct s5p_mfc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_debug (int,char*) ; 
 int vb2_mmap (int /*<<< orphan*/ *,struct vm_area_struct*) ; 

__attribute__((used)) static int s5p_mfc_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct s5p_mfc_ctx *ctx = fh_to_ctx(file->private_data);
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	int ret;

	if (offset < DST_QUEUE_OFF_BASE) {
		mfc_debug(2, "mmaping source\n");
		ret = vb2_mmap(&ctx->vq_src, vma);
	} else {		/* capture */
		mfc_debug(2, "mmaping destination\n");
		vma->vm_pgoff -= (DST_QUEUE_OFF_BASE >> PAGE_SHIFT);
		ret = vb2_mmap(&ctx->vq_dst, vma);
	}
	return ret;
}