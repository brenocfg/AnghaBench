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
struct sfi_table_header {int dummy; } ;
struct acpi_table_header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct acpi_table_header *sfi_to_acpi_th(
				struct sfi_table_header *th)
{
	return (struct acpi_table_header *)th;
}