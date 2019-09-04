#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u64 ;
struct amd64_pvt {TYPE_2__* ranges; } ;
struct TYPE_6__ {int x86; } ;
struct TYPE_4__ {scalar_t__ hi; scalar_t__ lo; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 TYPE_3__ boot_cpu_data ; 

__attribute__((used)) static inline u64 get_dram_base(struct amd64_pvt *pvt, u8 i)
{
	u64 addr = ((u64)pvt->ranges[i].base.lo & 0xffff0000) << 8;

	if (boot_cpu_data.x86 == 0xf)
		return addr;

	return (((u64)pvt->ranges[i].base.hi & 0x000000ff) << 40) | addr;
}