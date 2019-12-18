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
struct TYPE_2__ {int x86_model; } ;

/* Variables and functions */
#define  INTEL_FAM6_ATOM_GOLDMONT 131 
#define  INTEL_FAM6_ATOM_GOLDMONT_PLUS 130 
#define  INTEL_FAM6_IVYBRIDGE_X 129 
#define  INTEL_FAM6_SKYLAKE 128 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  bxt_idle_state_table_update () ; 
 int /*<<< orphan*/  ivt_idle_state_table_update () ; 
 int /*<<< orphan*/  sklh_idle_state_table_update () ; 

__attribute__((used)) static void intel_idle_state_table_update(void)
{
	switch (boot_cpu_data.x86_model) {

	case INTEL_FAM6_IVYBRIDGE_X:
		ivt_idle_state_table_update();
		break;
	case INTEL_FAM6_ATOM_GOLDMONT:
	case INTEL_FAM6_ATOM_GOLDMONT_PLUS:
		bxt_idle_state_table_update();
		break;
	case INTEL_FAM6_SKYLAKE:
		sklh_idle_state_table_update();
		break;
	}
}