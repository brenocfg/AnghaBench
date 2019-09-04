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
typedef  int u32 ;
struct uni_table_desc {int /*<<< orphan*/  entry_size; int /*<<< orphan*/  findex; } ;
struct uni_data_desc {int /*<<< orphan*/  size; int /*<<< orphan*/  findex; } ;
struct qlcnic_adapter {size_t file_prd_off; TYPE_1__* fw; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int EINVAL ; 
 int QLCNIC_UNI_BOOTLD_IDX_OFF ; 
 int /*<<< orphan*/  QLCNIC_UNI_DIR_SECT_BOOTLD ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct uni_table_desc* qlcnic_get_table_desc (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlcnic_validate_bootld(struct qlcnic_adapter *adapter)
{
	struct uni_table_desc *tab_desc;
	struct uni_data_desc *descr;
	u32 offs, tab_size, data_size, idx;
	const u8 *unirom = adapter->fw->data;
	__le32 temp;

	temp = *((__le32 *)&unirom[adapter->file_prd_off] +
		 QLCNIC_UNI_BOOTLD_IDX_OFF);
	idx = le32_to_cpu(temp);
	tab_desc = qlcnic_get_table_desc(unirom, QLCNIC_UNI_DIR_SECT_BOOTLD);

	if (!tab_desc)
		return -EINVAL;

	tab_size = le32_to_cpu(tab_desc->findex) +
		   le32_to_cpu(tab_desc->entry_size) * (idx + 1);

	if (adapter->fw->size < tab_size)
		return -EINVAL;

	offs = le32_to_cpu(tab_desc->findex) +
	       le32_to_cpu(tab_desc->entry_size) * idx;
	descr = (struct uni_data_desc *)&unirom[offs];

	data_size = le32_to_cpu(descr->findex) + le32_to_cpu(descr->size);

	if (adapter->fw->size < data_size)
		return -EINVAL;

	return 0;
}