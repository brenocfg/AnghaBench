#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ from; scalar_t__ to; scalar_t__ host; scalar_t__ fw; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* fw_mapping ; 

__attribute__((used)) static u32 wmi_addr_remap(u32 x)
{
	uint i;

	for (i = 0; i < ARRAY_SIZE(fw_mapping); i++) {
		if (fw_mapping[i].fw &&
		    ((x >= fw_mapping[i].from) && (x < fw_mapping[i].to)))
			return x + fw_mapping[i].host - fw_mapping[i].from;
	}

	return 0;
}