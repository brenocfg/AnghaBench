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
struct amdgpu_device {int /*<<< orphan*/  atif; int /*<<< orphan*/  acpi_nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_acpi_notifier (int /*<<< orphan*/ *) ; 

void amdgpu_acpi_fini(struct amdgpu_device *adev)
{
	unregister_acpi_notifier(&adev->acpi_nb);
	kfree(adev->atif);
}