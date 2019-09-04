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
struct vga_switcheroo_handler {int dummy; } ;
typedef  enum vga_switcheroo_handler_flags_t { ____Placeholder_vga_switcheroo_handler_flags_t } vga_switcheroo_handler_flags_t ;
struct TYPE_2__ {int handler_flags; struct vga_switcheroo_handler const* handler; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  vga_switcheroo_enable () ; 
 scalar_t__ vga_switcheroo_ready () ; 
 int /*<<< orphan*/  vgasr_mutex ; 
 TYPE_1__ vgasr_priv ; 

int vga_switcheroo_register_handler(
			  const struct vga_switcheroo_handler *handler,
			  enum vga_switcheroo_handler_flags_t handler_flags)
{
	mutex_lock(&vgasr_mutex);
	if (vgasr_priv.handler) {
		mutex_unlock(&vgasr_mutex);
		return -EINVAL;
	}

	vgasr_priv.handler = handler;
	vgasr_priv.handler_flags = handler_flags;
	if (vga_switcheroo_ready()) {
		pr_info("enabled\n");
		vga_switcheroo_enable();
	}
	mutex_unlock(&vgasr_mutex);
	return 0;
}