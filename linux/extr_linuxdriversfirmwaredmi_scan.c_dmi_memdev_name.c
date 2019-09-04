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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ handle; char* bank; char* device; } ;

/* Variables and functions */
 TYPE_1__* dmi_memdev ; 
 int dmi_memdev_nr ; 

void dmi_memdev_name(u16 handle, const char **bank, const char **device)
{
	int n;

	if (dmi_memdev == NULL)
		return;

	for (n = 0; n < dmi_memdev_nr; n++) {
		if (handle == dmi_memdev[n].handle) {
			*bank = dmi_memdev[n].bank;
			*device = dmi_memdev[n].device;
			break;
		}
	}
}