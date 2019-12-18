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
struct vga_switcheroo_client {int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 scalar_t__ VGA_SWITCHEROO_OFF ; 
 struct vga_switcheroo_client* find_active_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_set_default_device (int /*<<< orphan*/ ) ; 
 scalar_t__ vga_switcheroo_pwr_state (struct vga_switcheroo_client*) ; 
 int /*<<< orphan*/  vga_switchon (struct vga_switcheroo_client*) ; 
 TYPE_1__ vgasr_priv ; 

__attribute__((used)) static int vga_switchto_stage1(struct vga_switcheroo_client *new_client)
{
	struct vga_switcheroo_client *active;

	active = find_active_client(&vgasr_priv.clients);
	if (!active)
		return 0;

	if (vga_switcheroo_pwr_state(new_client) == VGA_SWITCHEROO_OFF)
		vga_switchon(new_client);

	vga_set_default_device(new_client->pdev);
	return 0;
}