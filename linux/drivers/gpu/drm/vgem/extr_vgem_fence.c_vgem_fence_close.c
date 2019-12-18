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
struct vgem_file {int /*<<< orphan*/  fence_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vgem_fence_idr_fini ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vgem_file*) ; 

void vgem_fence_close(struct vgem_file *vfile)
{
	idr_for_each(&vfile->fence_idr, __vgem_fence_idr_fini, vfile);
	idr_destroy(&vfile->fence_idr);
}