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
struct vme_user_vma_priv {int /*<<< orphan*/  refcnt; } ;
struct vm_area_struct {struct vme_user_vma_priv* vm_private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vme_user_vm_open(struct vm_area_struct *vma)
{
	struct vme_user_vma_priv *vma_priv = vma->vm_private_data;

	refcount_inc(&vma_priv->refcnt);
}