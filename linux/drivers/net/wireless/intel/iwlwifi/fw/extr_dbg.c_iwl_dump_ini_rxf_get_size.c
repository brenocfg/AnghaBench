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
typedef  int u32 ;
struct iwl_ini_rxf_data {scalar_t__ size; } ;
struct iwl_fw_runtime {int dummy; } ;
struct TYPE_2__ {scalar_t__ header_only; int /*<<< orphan*/  num_of_registers; } ;
struct iwl_fw_ini_region_cfg {TYPE_1__ fifos; } ;
struct iwl_fw_ini_error_dump_register {int dummy; } ;
struct iwl_fw_ini_error_dump_range {int dummy; } ;
struct iwl_fw_ini_error_dump {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_ini_get_rxf_data (struct iwl_fw_runtime*,struct iwl_fw_ini_region_cfg*,struct iwl_ini_rxf_data*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 iwl_dump_ini_rxf_get_size(struct iwl_fw_runtime *fwrt,
				     struct iwl_fw_ini_region_cfg *reg)
{
	struct iwl_ini_rxf_data rx_data;
	u32 size = sizeof(struct iwl_fw_ini_error_dump) +
		sizeof(struct iwl_fw_ini_error_dump_range) +
		le32_to_cpu(reg->fifos.num_of_registers) *
		sizeof(struct iwl_fw_ini_error_dump_register);

	if (reg->fifos.header_only)
		return size;

	iwl_ini_get_rxf_data(fwrt, reg, &rx_data);
	size += rx_data.size;

	return size;
}