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

/* Variables and functions */
 int /*<<< orphan*/  _ipi_mask_cpu ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/ * sdei_firmware_call ; 

__attribute__((used)) static void sdei_mark_interface_broken(void)
{
	pr_err("disabling SDEI firmware interface\n");
	on_each_cpu(&_ipi_mask_cpu, NULL, true);
	sdei_firmware_call = NULL;
}