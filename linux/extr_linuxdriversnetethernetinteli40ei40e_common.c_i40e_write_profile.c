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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_section_table {size_t section_count; int* section_offset; } ;
struct i40e_profile_segment {size_t device_table_count; TYPE_1__* device_table; } ;
struct TYPE_4__ {scalar_t__ type; size_t size; } ;
struct i40e_profile_section_header {TYPE_2__ section; } ;
struct i40e_hw {size_t device_id; } ;
typedef  int i40e_status ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
struct TYPE_3__ {size_t vendor_dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_DEBUG_PACKAGE ; 
 int I40E_ERR_DEVICE_NOT_SUPPORTED ; 
 size_t PCI_VENDOR_ID_INTEL ; 
 scalar_t__ SECTION_TYPE_MMIO ; 
 int i40e_aq_write_ddp (struct i40e_hw*,void*,int /*<<< orphan*/ ,size_t,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int /*<<< orphan*/ ,char*,...) ; 

enum i40e_status_code
i40e_write_profile(struct i40e_hw *hw, struct i40e_profile_segment *profile,
		   u32 track_id)
{
	i40e_status status = 0;
	struct i40e_section_table *sec_tbl;
	struct i40e_profile_section_header *sec = NULL;
	u32 dev_cnt;
	u32 vendor_dev_id;
	u32 *nvm;
	u32 section_size = 0;
	u32 offset = 0, info = 0;
	u32 i;

	dev_cnt = profile->device_table_count;

	for (i = 0; i < dev_cnt; i++) {
		vendor_dev_id = profile->device_table[i].vendor_dev_id;
		if ((vendor_dev_id >> 16) == PCI_VENDOR_ID_INTEL)
			if (hw->device_id == (vendor_dev_id & 0xFFFF))
				break;
	}
	if (i == dev_cnt) {
		i40e_debug(hw, I40E_DEBUG_PACKAGE, "Device doesn't support DDP");
		return I40E_ERR_DEVICE_NOT_SUPPORTED;
	}

	nvm = (u32 *)&profile->device_table[dev_cnt];
	sec_tbl = (struct i40e_section_table *)&nvm[nvm[0] + 1];

	for (i = 0; i < sec_tbl->section_count; i++) {
		sec = (struct i40e_profile_section_header *)((u8 *)profile +
					     sec_tbl->section_offset[i]);

		/* Skip 'AQ', 'note' and 'name' sections */
		if (sec->section.type != SECTION_TYPE_MMIO)
			continue;

		section_size = sec->section.size +
			sizeof(struct i40e_profile_section_header);

		/* Write profile */
		status = i40e_aq_write_ddp(hw, (void *)sec, (u16)section_size,
					   track_id, &offset, &info, NULL);
		if (status) {
			i40e_debug(hw, I40E_DEBUG_PACKAGE,
				   "Failed to write profile: offset %d, info %d",
				   offset, info);
			break;
		}
	}
	return status;
}