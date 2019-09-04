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
struct ib_mad_mgmt_vendor_class_table {scalar_t__* vendor_class; } ;

/* Variables and functions */
 int MAX_MGMT_VENDOR_RANGE2 ; 

__attribute__((used)) static int check_vendor_table(struct ib_mad_mgmt_vendor_class_table *vendor)
{
	int i;

	for (i = 0; i < MAX_MGMT_VENDOR_RANGE2; i++)
		if (vendor->vendor_class[i])
			return 1;

	return 0;
}