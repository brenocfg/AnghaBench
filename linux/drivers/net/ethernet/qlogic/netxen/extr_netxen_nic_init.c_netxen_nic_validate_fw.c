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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct uni_table_desc {int findex; int entry_size; } ;
struct uni_data_desc {int findex; int size; } ;
struct netxen_adapter {size_t file_prd_off; TYPE_1__* fw; } ;
typedef  int __le32 ;
struct TYPE_2__ {size_t size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NX_UNI_DIR_SECT_FW ; 
 int NX_UNI_FIRMWARE_IDX_OFF ; 
 int cpu_to_le32 (int) ; 
 struct uni_table_desc* nx_get_table_desc (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netxen_nic_validate_fw(struct netxen_adapter *adapter)
{
	struct uni_table_desc *tab_desc;
	struct uni_data_desc *descr;
	const u8 *unirom = adapter->fw->data;
	__le32 idx = cpu_to_le32(*((int *)&unirom[adapter->file_prd_off] +
				NX_UNI_FIRMWARE_IDX_OFF));
	u32 offs;
	u32 tab_size;
	u32 data_size;

	tab_desc = nx_get_table_desc(unirom, NX_UNI_DIR_SECT_FW);

	if (!tab_desc)
		return -EINVAL;

	tab_size = cpu_to_le32(tab_desc->findex) +
			(cpu_to_le32(tab_desc->entry_size) * (idx + 1));

	if (adapter->fw->size < tab_size)
		return -EINVAL;

	offs = cpu_to_le32(tab_desc->findex) +
		(cpu_to_le32(tab_desc->entry_size) * (idx));
	descr = (struct uni_data_desc *)&unirom[offs];
	data_size = cpu_to_le32(descr->findex) + cpu_to_le32(descr->size);

	if (adapter->fw->size < data_size)
		return -EINVAL;

	return 0;
}