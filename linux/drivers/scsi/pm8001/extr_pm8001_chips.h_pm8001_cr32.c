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
typedef  size_t u32 ;
struct pm8001_hba_info {TYPE_1__* io_mem; } ;
struct TYPE_2__ {size_t memvirtaddr; } ;

/* Variables and functions */
 size_t readl (size_t) ; 

__attribute__((used)) static inline u32 pm8001_cr32(struct pm8001_hba_info *pm8001_ha, u32 bar,
		u32 offset)
{
	return readl(pm8001_ha->io_mem[bar].memvirtaddr + offset);
}