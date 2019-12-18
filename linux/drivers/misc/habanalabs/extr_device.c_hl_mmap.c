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
struct vm_area_struct {int vm_pgoff; } ;
struct hl_fpriv {int dummy; } ;
struct file {struct hl_fpriv* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int HL_MMAP_CB_MASK ; 
 int hl_cb_mmap (struct hl_fpriv*,struct vm_area_struct*) ; 

__attribute__((used)) static int hl_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct hl_fpriv *hpriv = filp->private_data;

	if ((vma->vm_pgoff & HL_MMAP_CB_MASK) == HL_MMAP_CB_MASK) {
		vma->vm_pgoff ^= HL_MMAP_CB_MASK;
		return hl_cb_mmap(hpriv, vma);
	}

	return -EINVAL;
}