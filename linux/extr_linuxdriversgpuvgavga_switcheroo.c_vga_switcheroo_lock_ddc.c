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
struct pci_dev {int dummy; } ;
typedef  enum vga_switcheroo_client_id { ____Placeholder_vga_switcheroo_client_id } vga_switcheroo_client_id ;
struct TYPE_4__ {int old_ddc_owner; TYPE_1__* handler; int /*<<< orphan*/  mux_hw_lock; } ;
struct TYPE_3__ {int (* switch_ddc ) (int) ;int (* get_client_id ) (struct pci_dev*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int stub1 (struct pci_dev*) ; 
 int stub2 (int) ; 
 TYPE_2__ vgasr_priv ; 

int vga_switcheroo_lock_ddc(struct pci_dev *pdev)
{
	enum vga_switcheroo_client_id id;

	mutex_lock(&vgasr_priv.mux_hw_lock);
	if (!vgasr_priv.handler || !vgasr_priv.handler->switch_ddc) {
		vgasr_priv.old_ddc_owner = -ENODEV;
		return -ENODEV;
	}

	id = vgasr_priv.handler->get_client_id(pdev);
	vgasr_priv.old_ddc_owner = vgasr_priv.handler->switch_ddc(id);
	return vgasr_priv.old_ddc_owner;
}