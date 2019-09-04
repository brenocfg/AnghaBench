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
struct vga_switcheroo_client_ops {int /*<<< orphan*/  (* gpu_bound ) (struct pci_dev*,int) ;} ;
struct pci_dev {int dummy; } ;
typedef  enum vga_switcheroo_client_id { ____Placeholder_vga_switcheroo_client_id } vga_switcheroo_client_id ;
struct TYPE_4__ {TYPE_1__* handler; scalar_t__ active; } ;
struct TYPE_3__ {int (* get_client_id ) (struct pci_dev*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ID_BIT_AUDIO ; 
 int VGA_SWITCHEROO_UNKNOWN_ID ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int register_client (struct pci_dev*,struct vga_switcheroo_client_ops const*,int,struct pci_dev*,int,int) ; 
 int stub1 (struct pci_dev*) ; 
 int /*<<< orphan*/  stub2 (struct pci_dev*,int) ; 
 int /*<<< orphan*/  vgasr_mutex ; 
 TYPE_2__ vgasr_priv ; 

int vga_switcheroo_register_audio_client(struct pci_dev *pdev,
			const struct vga_switcheroo_client_ops *ops,
			struct pci_dev *vga_dev)
{
	enum vga_switcheroo_client_id id = VGA_SWITCHEROO_UNKNOWN_ID;

	/*
	 * if vga_switcheroo has enabled, that mean two GPU clients and also
	 * handler are registered. Get audio client id from bound GPU client
	 * id directly, otherwise, set it as VGA_SWITCHEROO_UNKNOWN_ID,
	 * it will set to correct id in later when vga_switcheroo_enable()
	 * is called.
	 */
	mutex_lock(&vgasr_mutex);
	if (vgasr_priv.active) {
		id = vgasr_priv.handler->get_client_id(vga_dev);
		if (id < 0) {
			mutex_unlock(&vgasr_mutex);
			return -EINVAL;
		}
		/* notify if GPU has been already bound */
		if (ops->gpu_bound)
			ops->gpu_bound(pdev, id);
	}
	mutex_unlock(&vgasr_mutex);

	return register_client(pdev, ops, id | ID_BIT_AUDIO, vga_dev,
			       false, true);
}