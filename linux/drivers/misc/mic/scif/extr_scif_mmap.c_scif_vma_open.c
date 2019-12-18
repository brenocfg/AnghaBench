#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vma_pvt {int /*<<< orphan*/  ref; int /*<<< orphan*/  ep; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; struct vma_pvt* vm_private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  this_device; } ;
struct TYPE_4__ {TYPE_1__ mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 TYPE_2__ scif_info ; 
 int /*<<< orphan*/  scif_insert_vma (int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static void scif_vma_open(struct vm_area_struct *vma)
{
	struct vma_pvt *vmapvt = vma->vm_private_data;

	dev_dbg(scif_info.mdev.this_device,
		"SCIFAPI vma open: vma_start 0x%lx vma_end 0x%lx\n",
		vma->vm_start, vma->vm_end);
	scif_insert_vma(vmapvt->ep, vma);
	kref_get(&vmapvt->ref);
}