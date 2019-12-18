#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cxl_afu {size_t slice; int /*<<< orphan*/  dev; int /*<<< orphan*/  current_mode; TYPE_1__* adapter; TYPE_2__* guest; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* afu_deactivate_mode ) (struct cxl_afu*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int handle_err; int /*<<< orphan*/  work_err; } ;
struct TYPE_4__ {int /*<<< orphan*/  afu_list_lock; int /*<<< orphan*/ ** afu; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_context_detach_all (struct cxl_afu*) ; 
 TYPE_3__* cxl_ops ; 
 int /*<<< orphan*/  cxl_pci_vphb_remove (struct cxl_afu*) ; 
 int /*<<< orphan*/  cxl_sysfs_afu_remove (struct cxl_afu*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  guest_release_serr_irq (struct cxl_afu*) ; 
 int /*<<< orphan*/  guest_unmap_slice_regs (struct cxl_afu*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cxl_afu*,int /*<<< orphan*/ ) ; 

void cxl_guest_remove_afu(struct cxl_afu *afu)
{
	if (!afu)
		return;

	/* flush and stop pending job */
	afu->guest->handle_err = false;
	flush_delayed_work(&afu->guest->work_err);

	cxl_pci_vphb_remove(afu);
	cxl_sysfs_afu_remove(afu);

	spin_lock(&afu->adapter->afu_list_lock);
	afu->adapter->afu[afu->slice] = NULL;
	spin_unlock(&afu->adapter->afu_list_lock);

	cxl_context_detach_all(afu);
	cxl_ops->afu_deactivate_mode(afu, afu->current_mode);
	guest_release_serr_irq(afu);
	guest_unmap_slice_regs(afu);

	device_unregister(&afu->dev);
}