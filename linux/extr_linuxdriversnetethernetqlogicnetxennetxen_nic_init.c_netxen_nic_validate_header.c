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
typedef  scalar_t__ u32 ;
struct uni_table_desc {int /*<<< orphan*/  findex; int /*<<< orphan*/  entry_size; int /*<<< orphan*/  num_entries; } ;
struct netxen_adapter {TYPE_1__* fw; } ;
typedef  int __le32 ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ QLCNIC_FILEHEADER_SIZE ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netxen_nic_validate_header(struct netxen_adapter *adapter)
{
	const u8 *unirom = adapter->fw->data;
	struct uni_table_desc *directory = (struct uni_table_desc *) &unirom[0];
	u32 fw_file_size = adapter->fw->size;
	u32 tab_size;
	__le32 entries;
	__le32 entry_size;

	if (fw_file_size < QLCNIC_FILEHEADER_SIZE)
		return -EINVAL;

	entries = cpu_to_le32(directory->num_entries);
	entry_size = cpu_to_le32(directory->entry_size);
	tab_size = cpu_to_le32(directory->findex) + (entries * entry_size);

	if (fw_file_size < tab_size)
		return -EINVAL;

	return 0;
}