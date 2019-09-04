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
typedef  int __u8 ;
struct TYPE_2__ {int family; } ;

/* Variables and functions */
 TYPE_1__* local_cpu_data ; 

__attribute__((used)) static char *get_cpu_type(void)
{
	__u8 family = local_cpu_data->family;

	switch (family) {
		case 0x07:
			return "ia64/itanium";
		case 0x1f:
			return "ia64/itanium2";
		default:
			return "ia64/ia64";
	}
}