#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {scalar_t__ vddc; } ;
struct si_ulv_param {TYPE_5__ pl; scalar_t__ supported; } ;
struct TYPE_7__ {int /*<<< orphan*/  valid_flag; int /*<<< orphan*/  last; int /*<<< orphan*/ * mc_reg_table_entry; } ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;
struct si_power_info {int /*<<< orphan*/  sram_end; int /*<<< orphan*/  mc_reg_table_start; TYPE_1__ mc_reg_table; TYPE_2__ smc_mc_reg_table; struct si_ulv_param ulv; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct ni_ps {TYPE_5__* performance_levels; } ;
typedef  TYPE_2__ SMC_SIslands_MCRegisters ;

/* Variables and functions */
 size_t SISLANDS_MCREGISTERTABLE_ACPI_SLOT ; 
 size_t SISLANDS_MCREGISTERTABLE_INITIAL_SLOT ; 
 size_t SISLANDS_MCREGISTERTABLE_ULV_SLOT ; 
 int /*<<< orphan*/  SI_SMC_SOFT_REGISTER_seq_index ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 int /*<<< orphan*/  si_convert_mc_reg_table_entry_to_smc (struct radeon_device*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si_convert_mc_reg_table_to_smc (struct radeon_device*,struct radeon_ps*,TYPE_2__*) ; 
 int /*<<< orphan*/  si_convert_mc_registers (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si_copy_bytes_to_smc (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  si_populate_mc_reg_addresses (struct radeon_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  si_write_smc_soft_register (struct radeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si_populate_mc_reg_table(struct radeon_device *rdev,
				    struct radeon_ps *radeon_boot_state)
{
	struct ni_ps *boot_state = ni_get_ps(radeon_boot_state);
	struct si_power_info *si_pi = si_get_pi(rdev);
	struct si_ulv_param *ulv = &si_pi->ulv;
	SMC_SIslands_MCRegisters *smc_mc_reg_table = &si_pi->smc_mc_reg_table;

	memset(smc_mc_reg_table, 0, sizeof(SMC_SIslands_MCRegisters));

	si_write_smc_soft_register(rdev, SI_SMC_SOFT_REGISTER_seq_index, 1);

	si_populate_mc_reg_addresses(rdev, smc_mc_reg_table);

	si_convert_mc_reg_table_entry_to_smc(rdev, &boot_state->performance_levels[0],
					     &smc_mc_reg_table->data[SISLANDS_MCREGISTERTABLE_INITIAL_SLOT]);

	si_convert_mc_registers(&si_pi->mc_reg_table.mc_reg_table_entry[0],
				&smc_mc_reg_table->data[SISLANDS_MCREGISTERTABLE_ACPI_SLOT],
				si_pi->mc_reg_table.last,
				si_pi->mc_reg_table.valid_flag);

	if (ulv->supported && ulv->pl.vddc != 0)
		si_convert_mc_reg_table_entry_to_smc(rdev, &ulv->pl,
						     &smc_mc_reg_table->data[SISLANDS_MCREGISTERTABLE_ULV_SLOT]);
	else
		si_convert_mc_registers(&si_pi->mc_reg_table.mc_reg_table_entry[0],
					&smc_mc_reg_table->data[SISLANDS_MCREGISTERTABLE_ULV_SLOT],
					si_pi->mc_reg_table.last,
					si_pi->mc_reg_table.valid_flag);

	si_convert_mc_reg_table_to_smc(rdev, radeon_boot_state, smc_mc_reg_table);

	return si_copy_bytes_to_smc(rdev, si_pi->mc_reg_table_start,
				    (u8 *)smc_mc_reg_table,
				    sizeof(SMC_SIslands_MCRegisters), si_pi->sram_end);
}