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
struct uni_data_desc {int dummy; } ;
struct qlcnic_adapter {size_t file_prd_off; TYPE_1__* fw; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct uni_table_desc* qlcnic_get_table_desc (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static
struct uni_data_desc *qlcnic_get_data_desc(struct qlcnic_adapter *adapter,
			u32 section, u32 idx_offset)
{
	const u8 *unirom = adapter->fw->data;
	struct uni_table_desc *tab_desc;
	u32 offs, idx;
	__le32 temp;

	temp = *((__le32 *)&unirom[adapter->file_prd_off] + idx_offset);
	idx = le32_to_cpu(temp);

	tab_desc = qlcnic_get_table_desc(unirom, section);

	if (tab_desc == NULL)
		return NULL;

	offs = le32_to_cpu(tab_desc->findex) +
	       le32_to_cpu(tab_desc->entry_size) * idx;

	return (struct uni_data_desc *)&unirom[offs];
}