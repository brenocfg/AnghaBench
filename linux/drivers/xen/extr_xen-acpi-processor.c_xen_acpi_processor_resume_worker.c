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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ids_done ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_acpi_bits ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int xen_upload_processor_pm_data () ; 

__attribute__((used)) static void xen_acpi_processor_resume_worker(struct work_struct *dummy)
{
	int rc;

	bitmap_zero(acpi_ids_done, nr_acpi_bits);

	rc = xen_upload_processor_pm_data();
	if (rc != 0)
		pr_info("ACPI data upload failed, error = %d\n", rc);
}