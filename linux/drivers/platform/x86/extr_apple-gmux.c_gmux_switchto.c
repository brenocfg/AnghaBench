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
typedef  enum vga_switcheroo_client_id { ____Placeholder_vga_switcheroo_client_id } vga_switcheroo_client_id ;
struct TYPE_3__ {int switch_state_ddc; int switch_state_display; int switch_state_external; scalar_t__ external_switchable; } ;

/* Variables and functions */
 TYPE_1__* apple_gmux_data ; 
 int /*<<< orphan*/  gmux_write_switch_state (TYPE_1__*) ; 

__attribute__((used)) static int gmux_switchto(enum vga_switcheroo_client_id id)
{
	apple_gmux_data->switch_state_ddc = id;
	apple_gmux_data->switch_state_display = id;
	if (apple_gmux_data->external_switchable)
		apple_gmux_data->switch_state_external = id;

	gmux_write_switch_state(apple_gmux_data);

	return 0;
}