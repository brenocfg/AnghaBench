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
struct gb_interface {int active; int /*<<< orphan*/  mode_switch_completion; scalar_t__ mode_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_interface_hibernate_link (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_interface_refclk_set (struct gb_interface*,int) ; 
 int /*<<< orphan*/  gb_interface_route_destroy (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_interface_unipro_set (struct gb_interface*,int) ; 
 int /*<<< orphan*/  gb_interface_vsys_set (struct gb_interface*,int) ; 
 int /*<<< orphan*/  trace_gb_interface_deactivate (struct gb_interface*) ; 

void gb_interface_deactivate(struct gb_interface *intf)
{
	if (!intf->active)
		return;

	trace_gb_interface_deactivate(intf);

	/* Abort any ongoing mode switch. */
	if (intf->mode_switch)
		complete(&intf->mode_switch_completion);

	gb_interface_route_destroy(intf);
	gb_interface_hibernate_link(intf);
	gb_interface_unipro_set(intf, false);
	gb_interface_refclk_set(intf, false);
	gb_interface_vsys_set(intf, false);

	intf->active = false;
}