#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ucNumOfVRAMModule; int /*<<< orphan*/  usMemClkPatchTblOffset; } ;
union vram_info {TYPE_2__ v2_1; } ;
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_8__ {TYPE_7__* atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct atom_mc_reg_table {int last; int num_entries; TYPE_4__* mc_reg_table_entry; TYPE_3__* mc_reg_address; } ;
struct TYPE_14__ {scalar_t__ bios; } ;
struct TYPE_13__ {int /*<<< orphan*/  usRegDataBlkSize; int /*<<< orphan*/  usRegIndexTblSize; TYPE_5__* asRegIndexBuf; } ;
struct TYPE_12__ {int ucPreRegDataLength; int /*<<< orphan*/  usRegIndex; } ;
struct TYPE_11__ {int mclk_max; int* mc_data; } ;
struct TYPE_10__ {int pre_reg_data; scalar_t__ s1; } ;
typedef  int /*<<< orphan*/  ATOM_MEMORY_SETTING_DATA_BLOCK ;
typedef  TYPE_5__ ATOM_INIT_REG_INDEX_FORMAT ;
typedef  TYPE_6__ ATOM_INIT_REG_BLOCK ;

/* Variables and functions */
 int ACCESS_PLACEHOLDER ; 
 int CLOCK_RANGE_MASK ; 
 int CLOCK_RANGE_SHIFT ; 
 int /*<<< orphan*/  DATA ; 
 int DATA_EQU_PREV ; 
 int DATA_FROM_TABLE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int EINVAL ; 
 int END_OF_REG_DATA_BLOCK ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LOW_NIBBLE_MASK ; 
 int MEM_ID_MASK ; 
 int MEM_ID_SHIFT ; 
 int VBIOS_MAX_AC_TIMING_ENTRIES ; 
 int VBIOS_MC_REGISTER_ARRAY_SIZE ; 
 int /*<<< orphan*/  VRAM_Info ; 
 scalar_t__ atom_parse_data_header (TYPE_7__*,int,scalar_t__*,int*,int*,scalar_t__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  memset (struct atom_mc_reg_table*,int /*<<< orphan*/ ,int) ; 

int radeon_atom_init_mc_reg_table(struct radeon_device *rdev,
				  u8 module_index,
				  struct atom_mc_reg_table *reg_table)
{
	int index = GetIndexIntoMasterTable(DATA, VRAM_Info);
	u8 frev, crev, num_entries, t_mem_id, num_ranges = 0;
	u32 i = 0, j;
	u16 data_offset, size;
	union vram_info *vram_info;

	memset(reg_table, 0, sizeof(struct atom_mc_reg_table));

	if (atom_parse_data_header(rdev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) {
		vram_info = (union vram_info *)
			(rdev->mode_info.atom_context->bios + data_offset);
		switch (frev) {
		case 1:
			DRM_ERROR("old table version %d, %d\n", frev, crev);
			return -EINVAL;
		case 2:
			switch (crev) {
			case 1:
				if (module_index < vram_info->v2_1.ucNumOfVRAMModule) {
					ATOM_INIT_REG_BLOCK *reg_block =
						(ATOM_INIT_REG_BLOCK *)
						((u8 *)vram_info + le16_to_cpu(vram_info->v2_1.usMemClkPatchTblOffset));
					ATOM_MEMORY_SETTING_DATA_BLOCK *reg_data =
						(ATOM_MEMORY_SETTING_DATA_BLOCK *)
						((u8 *)reg_block + (2 * sizeof(u16)) +
						 le16_to_cpu(reg_block->usRegIndexTblSize));
					ATOM_INIT_REG_INDEX_FORMAT *format = &reg_block->asRegIndexBuf[0];
					num_entries = (u8)((le16_to_cpu(reg_block->usRegIndexTblSize)) /
							   sizeof(ATOM_INIT_REG_INDEX_FORMAT)) - 1;
					if (num_entries > VBIOS_MC_REGISTER_ARRAY_SIZE)
						return -EINVAL;
					while (i < num_entries) {
						if (format->ucPreRegDataLength & ACCESS_PLACEHOLDER)
							break;
						reg_table->mc_reg_address[i].s1 =
							(u16)(le16_to_cpu(format->usRegIndex));
						reg_table->mc_reg_address[i].pre_reg_data =
							(u8)(format->ucPreRegDataLength);
						i++;
						format = (ATOM_INIT_REG_INDEX_FORMAT *)
							((u8 *)format + sizeof(ATOM_INIT_REG_INDEX_FORMAT));
					}
					reg_table->last = i;
					while ((le32_to_cpu(*(u32 *)reg_data) != END_OF_REG_DATA_BLOCK) &&
					       (num_ranges < VBIOS_MAX_AC_TIMING_ENTRIES)) {
						t_mem_id = (u8)((le32_to_cpu(*(u32 *)reg_data) & MEM_ID_MASK)
								>> MEM_ID_SHIFT);
						if (module_index == t_mem_id) {
							reg_table->mc_reg_table_entry[num_ranges].mclk_max =
								(u32)((le32_to_cpu(*(u32 *)reg_data) & CLOCK_RANGE_MASK)
								      >> CLOCK_RANGE_SHIFT);
							for (i = 0, j = 1; i < reg_table->last; i++) {
								if ((reg_table->mc_reg_address[i].pre_reg_data & LOW_NIBBLE_MASK) == DATA_FROM_TABLE) {
									reg_table->mc_reg_table_entry[num_ranges].mc_data[i] =
										(u32)le32_to_cpu(*((u32 *)reg_data + j));
									j++;
								} else if ((reg_table->mc_reg_address[i].pre_reg_data & LOW_NIBBLE_MASK) == DATA_EQU_PREV) {
									reg_table->mc_reg_table_entry[num_ranges].mc_data[i] =
										reg_table->mc_reg_table_entry[num_ranges].mc_data[i - 1];
								}
							}
							num_ranges++;
						}
						reg_data = (ATOM_MEMORY_SETTING_DATA_BLOCK *)
							((u8 *)reg_data + le16_to_cpu(reg_block->usRegDataBlkSize));
					}
					if (le32_to_cpu(*(u32 *)reg_data) != END_OF_REG_DATA_BLOCK)
						return -EINVAL;
					reg_table->num_entries = num_ranges;
				} else
					return -EINVAL;
				break;
			default:
				DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
				return -EINVAL;
			}
			break;
		default:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			return -EINVAL;
		}
		return 0;
	}
	return -EINVAL;
}