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
struct TYPE_2__ {int registered_clients; scalar_t__ handler; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 TYPE_1__ vgasr_priv ; 

__attribute__((used)) static bool vga_switcheroo_ready(void)
{
	/* we're ready if we get two clients + handler */
	return !vgasr_priv.active &&
	       vgasr_priv.registered_clients == 2 && vgasr_priv.handler;
}