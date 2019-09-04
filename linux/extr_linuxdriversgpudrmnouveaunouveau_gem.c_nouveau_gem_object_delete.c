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
struct nouveau_vma {int /*<<< orphan*/  fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_fence_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_vma_del (struct nouveau_vma**) ; 

__attribute__((used)) static void
nouveau_gem_object_delete(struct nouveau_vma *vma)
{
	nouveau_fence_unref(&vma->fence);
	nouveau_vma_del(&vma);
}