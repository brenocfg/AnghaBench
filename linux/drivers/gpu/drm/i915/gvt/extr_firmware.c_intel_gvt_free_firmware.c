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
struct TYPE_2__ {int /*<<< orphan*/  mmio; int /*<<< orphan*/  cfg_space; int /*<<< orphan*/  firmware_loaded; } ;
struct intel_gvt {TYPE_1__ firmware; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_firmware_sysfs (struct intel_gvt*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void intel_gvt_free_firmware(struct intel_gvt *gvt)
{
	if (!gvt->firmware.firmware_loaded)
		clean_firmware_sysfs(gvt);

	kfree(gvt->firmware.cfg_space);
	kfree(gvt->firmware.mmio);
}