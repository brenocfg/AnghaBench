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
struct TYPE_3__ {int active; int /*<<< orphan*/  mux_hw_lock; int /*<<< orphan*/ * handler; scalar_t__ handler_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  vga_switcheroo_debugfs_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  vgasr_mutex ; 
 TYPE_1__ vgasr_priv ; 

void vga_switcheroo_unregister_handler(void)
{
	mutex_lock(&vgasr_mutex);
	mutex_lock(&vgasr_priv.mux_hw_lock);
	vgasr_priv.handler_flags = 0;
	vgasr_priv.handler = NULL;
	if (vgasr_priv.active) {
		pr_info("disabled\n");
		vga_switcheroo_debugfs_fini(&vgasr_priv);
		vgasr_priv.active = false;
	}
	mutex_unlock(&vgasr_priv.mux_hw_lock);
	mutex_unlock(&vgasr_mutex);
}