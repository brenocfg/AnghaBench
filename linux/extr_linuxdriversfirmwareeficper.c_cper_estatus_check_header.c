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
struct acpi_hest_generic_status {int data_length; int raw_data_offset; scalar_t__ raw_data_length; } ;
struct acpi_hest_generic_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

int cper_estatus_check_header(const struct acpi_hest_generic_status *estatus)
{
	if (estatus->data_length &&
	    estatus->data_length < sizeof(struct acpi_hest_generic_data))
		return -EINVAL;
	if (estatus->raw_data_length &&
	    estatus->raw_data_offset < sizeof(*estatus) + estatus->data_length)
		return -EINVAL;

	return 0;
}