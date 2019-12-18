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
struct ib_mad_mgmt_vendor_class {scalar_t__* method_table; } ;

/* Variables and functions */
 int MAX_MGMT_OUI ; 

__attribute__((used)) static int check_vendor_class(struct ib_mad_mgmt_vendor_class *vendor_class)
{
	int i;

	for (i = 0; i < MAX_MGMT_OUI; i++)
		if (vendor_class->method_table[i])
			return 1;
	return 0;
}