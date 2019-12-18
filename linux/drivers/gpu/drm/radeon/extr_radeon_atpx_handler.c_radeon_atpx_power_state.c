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
typedef  enum vga_switcheroo_state { ____Placeholder_vga_switcheroo_state } vga_switcheroo_state ;
typedef  enum vga_switcheroo_client_id { ____Placeholder_vga_switcheroo_client_id } vga_switcheroo_client_id ;
struct TYPE_2__ {int /*<<< orphan*/  atpx; } ;

/* Variables and functions */
 int VGA_SWITCHEROO_IGD ; 
 TYPE_1__ radeon_atpx_priv ; 
 int /*<<< orphan*/  radeon_atpx_set_discrete_state (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int radeon_atpx_power_state(enum vga_switcheroo_client_id id,
				   enum vga_switcheroo_state state)
{
	/* on w500 ACPI can't change intel gpu state */
	if (id == VGA_SWITCHEROO_IGD)
		return 0;

	radeon_atpx_set_discrete_state(&radeon_atpx_priv.atpx, state);
	return 0;
}