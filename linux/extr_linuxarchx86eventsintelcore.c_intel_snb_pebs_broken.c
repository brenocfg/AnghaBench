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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int x86_model; scalar_t__ microcode; int /*<<< orphan*/  x86_stepping; } ;

/* Variables and functions */
#define  INTEL_FAM6_SANDYBRIDGE 129 
#define  INTEL_FAM6_SANDYBRIDGE_X 128 
 scalar_t__ UINT_MAX ; 
 TYPE_1__ cpu_data (int) ; 

__attribute__((used)) static int intel_snb_pebs_broken(int cpu)
{
	u32 rev = UINT_MAX; /* default to broken for unknown models */

	switch (cpu_data(cpu).x86_model) {
	case INTEL_FAM6_SANDYBRIDGE:
		rev = 0x28;
		break;

	case INTEL_FAM6_SANDYBRIDGE_X:
		switch (cpu_data(cpu).x86_stepping) {
		case 6: rev = 0x618; break;
		case 7: rev = 0x70c; break;
		}
	}

	return (cpu_data(cpu).microcode < rev);
}