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
struct vga_switcheroo_client {int /*<<< orphan*/  id; int /*<<< orphan*/  driver_power_control; } ;
struct pci_dev {int dummy; } ;
typedef  enum vga_switcheroo_state { ____Placeholder_vga_switcheroo_state } vga_switcheroo_state ;
struct TYPE_4__ {TYPE_1__* handler; int /*<<< orphan*/  clients; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* power_state ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 struct vga_switcheroo_client* find_client_from_pci (int /*<<< orphan*/ *,struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ vgasr_priv ; 

__attribute__((used)) static void vga_switcheroo_power_switch(struct pci_dev *pdev,
					enum vga_switcheroo_state state)
{
	struct vga_switcheroo_client *client;

	if (!vgasr_priv.handler->power_state)
		return;

	client = find_client_from_pci(&vgasr_priv.clients, pdev);
	if (!client)
		return;

	if (!client->driver_power_control)
		return;

	vgasr_priv.handler->power_state(client->id, state);
}