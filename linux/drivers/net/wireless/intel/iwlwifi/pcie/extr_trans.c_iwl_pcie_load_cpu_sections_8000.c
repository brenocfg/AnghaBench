#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct fw_img {int num_sec; TYPE_2__* sec; } ;
struct TYPE_4__ {scalar_t__ offset; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {scalar_t__ use_tfh; } ;

/* Variables and functions */
 scalar_t__ CPU1_CPU2_SEPARATOR_SECTION ; 
 int /*<<< orphan*/  FH_UCODE_LOAD_STATUS ; 
 int /*<<< orphan*/  IWL_DEBUG_FW (struct iwl_trans*,char*,int) ; 
 scalar_t__ PAGING_SEPARATOR_SECTION ; 
 int /*<<< orphan*/  UREG_UCODE_LOAD_STATUS ; 
 int /*<<< orphan*/  iwl_enable_interrupts (struct iwl_trans*) ; 
 int iwl_pcie_load_section (struct iwl_trans*,int,TYPE_2__*) ; 
 int iwl_read_direct32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_pcie_load_cpu_sections_8000(struct iwl_trans *trans,
					   const struct fw_img *image,
					   int cpu,
					   int *first_ucode_section)
{
	int shift_param;
	int i, ret = 0, sec_num = 0x1;
	u32 val, last_read_idx = 0;

	if (cpu == 1) {
		shift_param = 0;
		*first_ucode_section = 0;
	} else {
		shift_param = 16;
		(*first_ucode_section)++;
	}

	for (i = *first_ucode_section; i < image->num_sec; i++) {
		last_read_idx = i;

		/*
		 * CPU1_CPU2_SEPARATOR_SECTION delimiter - separate between
		 * CPU1 to CPU2.
		 * PAGING_SEPARATOR_SECTION delimiter - separate between
		 * CPU2 non paged to CPU2 paging sec.
		 */
		if (!image->sec[i].data ||
		    image->sec[i].offset == CPU1_CPU2_SEPARATOR_SECTION ||
		    image->sec[i].offset == PAGING_SEPARATOR_SECTION) {
			IWL_DEBUG_FW(trans,
				     "Break since Data not valid or Empty section, sec = %d\n",
				     i);
			break;
		}

		ret = iwl_pcie_load_section(trans, i, &image->sec[i]);
		if (ret)
			return ret;

		/* Notify ucode of loaded section number and status */
		val = iwl_read_direct32(trans, FH_UCODE_LOAD_STATUS);
		val = val | (sec_num << shift_param);
		iwl_write_direct32(trans, FH_UCODE_LOAD_STATUS, val);

		sec_num = (sec_num << 1) | 0x1;
	}

	*first_ucode_section = last_read_idx;

	iwl_enable_interrupts(trans);

	if (trans->trans_cfg->use_tfh) {
		if (cpu == 1)
			iwl_write_prph(trans, UREG_UCODE_LOAD_STATUS,
				       0xFFFF);
		else
			iwl_write_prph(trans, UREG_UCODE_LOAD_STATUS,
				       0xFFFFFFFF);
	} else {
		if (cpu == 1)
			iwl_write_direct32(trans, FH_UCODE_LOAD_STATUS,
					   0xFFFF);
		else
			iwl_write_direct32(trans, FH_UCODE_LOAD_STATUS,
					   0xFFFFFFFF);
	}

	return 0;
}