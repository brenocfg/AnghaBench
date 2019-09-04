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
struct dmi_header {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DMI_ENTRY_MEM_DEVICE ; 

__attribute__((used)) static void ghes_edac_count_dimms(const struct dmi_header *dh, void *arg)
{
	int *num_dimm = arg;

	if (dh->type == DMI_ENTRY_MEM_DEVICE)
		(*num_dimm)++;
}