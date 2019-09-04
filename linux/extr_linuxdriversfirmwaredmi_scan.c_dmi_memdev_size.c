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
typedef  unsigned long long u64 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ handle; unsigned long long size; } ;

/* Variables and functions */
 TYPE_1__* dmi_memdev ; 
 int dmi_memdev_nr ; 

u64 dmi_memdev_size(u16 handle)
{
	int n;

	if (dmi_memdev) {
		for (n = 0; n < dmi_memdev_nr; n++) {
			if (handle == dmi_memdev[n].handle)
				return dmi_memdev[n].size;
		}
	}
	return ~0ull;
}