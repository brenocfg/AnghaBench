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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
union acpi_object {TYPE_1__ integer; } ;
struct hpx_type3 {int /*<<< orphan*/  reg_mask_or; int /*<<< orphan*/  reg_mask_and; int /*<<< orphan*/  reg_offset; int /*<<< orphan*/  match_value; int /*<<< orphan*/  match_mask_and; int /*<<< orphan*/  match_offset; int /*<<< orphan*/  dvsec_rev; int /*<<< orphan*/  dvsec_id; int /*<<< orphan*/  pci_exp_vendor_id; int /*<<< orphan*/  pci_exp_cap_ver; int /*<<< orphan*/  pci_exp_cap_id; int /*<<< orphan*/  config_space_location; int /*<<< orphan*/  function_type; int /*<<< orphan*/  device_type; } ;

/* Variables and functions */

__attribute__((used)) static void parse_hpx3_register(struct hpx_type3 *hpx3_reg,
				union acpi_object *reg_fields)
{
	hpx3_reg->device_type            = reg_fields[0].integer.value;
	hpx3_reg->function_type          = reg_fields[1].integer.value;
	hpx3_reg->config_space_location  = reg_fields[2].integer.value;
	hpx3_reg->pci_exp_cap_id         = reg_fields[3].integer.value;
	hpx3_reg->pci_exp_cap_ver        = reg_fields[4].integer.value;
	hpx3_reg->pci_exp_vendor_id      = reg_fields[5].integer.value;
	hpx3_reg->dvsec_id               = reg_fields[6].integer.value;
	hpx3_reg->dvsec_rev              = reg_fields[7].integer.value;
	hpx3_reg->match_offset           = reg_fields[8].integer.value;
	hpx3_reg->match_mask_and         = reg_fields[9].integer.value;
	hpx3_reg->match_value            = reg_fields[10].integer.value;
	hpx3_reg->reg_offset             = reg_fields[11].integer.value;
	hpx3_reg->reg_mask_and           = reg_fields[12].integer.value;
	hpx3_reg->reg_mask_or            = reg_fields[13].integer.value;
}