#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct radeon_device {int dummy; } ;
struct TYPE_8__ {int last; int valid_flag; TYPE_2__* mc_reg_address; } ;
struct evergreen_power_info {TYPE_3__ mc_reg_table; } ;
struct TYPE_9__ {scalar_t__ last; TYPE_1__* address; } ;
struct TYPE_7__ {int /*<<< orphan*/  s1; int /*<<< orphan*/  s0; } ;
struct TYPE_6__ {void* s1; void* s0; } ;
typedef  TYPE_4__ SMC_Evergreen_MCRegisters ;

/* Variables and functions */
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void cypress_populate_mc_reg_addresses(struct radeon_device *rdev,
					      SMC_Evergreen_MCRegisters *mc_reg_table)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	u32 i, j;

	for (i = 0, j = 0; j < eg_pi->mc_reg_table.last; j++) {
		if (eg_pi->mc_reg_table.valid_flag & (1 << j)) {
			mc_reg_table->address[i].s0 =
				cpu_to_be16(eg_pi->mc_reg_table.mc_reg_address[j].s0);
			mc_reg_table->address[i].s1 =
				cpu_to_be16(eg_pi->mc_reg_table.mc_reg_address[j].s1);
			i++;
		}
	}

	mc_reg_table->last = (u8)i;
}