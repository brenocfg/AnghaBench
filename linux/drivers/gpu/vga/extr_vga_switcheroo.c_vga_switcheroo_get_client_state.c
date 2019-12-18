#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vga_switcheroo_client {int dummy; } ;
struct pci_dev {int dummy; } ;
typedef  enum vga_switcheroo_state { ____Placeholder_vga_switcheroo_state } vga_switcheroo_state ;
struct TYPE_2__ {int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int VGA_SWITCHEROO_NOT_FOUND ; 
 struct vga_switcheroo_client* find_client_from_pci (int /*<<< orphan*/ *,struct pci_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vga_switcheroo_pwr_state (struct vga_switcheroo_client*) ; 
 int /*<<< orphan*/  vgasr_mutex ; 
 TYPE_1__ vgasr_priv ; 

enum vga_switcheroo_state vga_switcheroo_get_client_state(struct pci_dev *pdev)
{
	struct vga_switcheroo_client *client;
	enum vga_switcheroo_state ret;

	mutex_lock(&vgasr_mutex);
	client = find_client_from_pci(&vgasr_priv.clients, pdev);
	if (!client)
		ret = VGA_SWITCHEROO_NOT_FOUND;
	else
		ret = vga_switcheroo_pwr_state(client);
	mutex_unlock(&vgasr_mutex);
	return ret;
}