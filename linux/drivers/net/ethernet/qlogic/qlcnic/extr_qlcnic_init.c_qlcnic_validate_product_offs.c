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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct uni_table_desc {int /*<<< orphan*/  entry_size; int /*<<< orphan*/  findex; int /*<<< orphan*/  num_entries; } ;
struct qlcnic_adapter {scalar_t__ file_prd_off; TYPE_2__* ahw; TYPE_1__* fw; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {scalar_t__ revision_id; } ;
struct TYPE_3__ {scalar_t__* data; scalar_t__ size; } ;

/* Variables and functions */
 int EINVAL ; 
 int QLCNIC_UNI_CHIP_REV_OFF ; 
 int /*<<< orphan*/  QLCNIC_UNI_DIR_SECT_PRODUCT_TBL ; 
 int QLCNIC_UNI_FLAGS_OFF ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct uni_table_desc* qlcnic_get_table_desc (scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int qlcnic_has_mn (struct qlcnic_adapter*) ; 

__attribute__((used)) static int
qlcnic_validate_product_offs(struct qlcnic_adapter *adapter)
{
	struct uni_table_desc *ptab_descr;
	const u8 *unirom = adapter->fw->data;
	int mn_present = qlcnic_has_mn(adapter);
	u32 entries, entry_size, tab_size, i;
	__le32 temp;

	ptab_descr = qlcnic_get_table_desc(unirom,
				QLCNIC_UNI_DIR_SECT_PRODUCT_TBL);
	if (!ptab_descr)
		return -EINVAL;

	entries = le32_to_cpu(ptab_descr->num_entries);
	entry_size = le32_to_cpu(ptab_descr->entry_size);
	tab_size = le32_to_cpu(ptab_descr->findex) + (entries * entry_size);

	if (adapter->fw->size < tab_size)
		return -EINVAL;

nomn:
	for (i = 0; i < entries; i++) {

		u32 flags, file_chiprev, offs;
		u8 chiprev = adapter->ahw->revision_id;
		u32 flagbit;

		offs = le32_to_cpu(ptab_descr->findex) +
		       i * le32_to_cpu(ptab_descr->entry_size);
		temp = *((__le32 *)&unirom[offs] + QLCNIC_UNI_FLAGS_OFF);
		flags = le32_to_cpu(temp);
		temp = *((__le32 *)&unirom[offs] + QLCNIC_UNI_CHIP_REV_OFF);
		file_chiprev = le32_to_cpu(temp);

		flagbit = mn_present ? 1 : 2;

		if ((chiprev == file_chiprev) &&
					((1ULL << flagbit) & flags)) {
			adapter->file_prd_off = offs;
			return 0;
		}
	}
	if (mn_present) {
		mn_present = 0;
		goto nomn;
	}
	return -EINVAL;
}