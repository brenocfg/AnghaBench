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
typedef  enum vga_switcheroo_handler_flags_t { ____Placeholder_vga_switcheroo_handler_flags_t } vga_switcheroo_handler_flags_t ;
struct TYPE_2__ {int handler_flags; } ;

/* Variables and functions */
 TYPE_1__ vgasr_priv ; 

enum vga_switcheroo_handler_flags_t vga_switcheroo_handler_flags(void)
{
	return vgasr_priv.handler_flags;
}