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
struct eeepc_laptop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_CAMERA ; 
 scalar_t__ get_acpi (struct eeepc_laptop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_acpi (struct eeepc_laptop*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void eeepc_enable_camera(struct eeepc_laptop *eeepc)
{
	/*
	 * If the following call to set_acpi() fails, it's because there's no
	 * camera so we can ignore the error.
	 */
	if (get_acpi(eeepc, CM_ASL_CAMERA) == 0)
		set_acpi(eeepc, CM_ASL_CAMERA, 1);
}