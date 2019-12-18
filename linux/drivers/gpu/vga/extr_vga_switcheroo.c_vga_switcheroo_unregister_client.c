#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vga_switcheroo_client {int /*<<< orphan*/  list; } ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int registered_clients; int active; int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 scalar_t__ client_is_vga (struct vga_switcheroo_client*) ; 
 struct vga_switcheroo_client* find_client_from_pci (int /*<<< orphan*/ *,struct pci_dev*) ; 
 int /*<<< orphan*/  kfree (struct vga_switcheroo_client*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  vga_switcheroo_debugfs_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  vgasr_mutex ; 
 TYPE_1__ vgasr_priv ; 

void vga_switcheroo_unregister_client(struct pci_dev *pdev)
{
	struct vga_switcheroo_client *client;

	mutex_lock(&vgasr_mutex);
	client = find_client_from_pci(&vgasr_priv.clients, pdev);
	if (client) {
		if (client_is_vga(client))
			vgasr_priv.registered_clients--;
		list_del(&client->list);
		kfree(client);
	}
	if (vgasr_priv.active && vgasr_priv.registered_clients < 2) {
		pr_info("disabled\n");
		vga_switcheroo_debugfs_fini(&vgasr_priv);
		vgasr_priv.active = false;
	}
	mutex_unlock(&vgasr_mutex);
}