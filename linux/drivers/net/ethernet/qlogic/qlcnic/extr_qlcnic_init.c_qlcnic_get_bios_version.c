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
struct qlcnic_adapter {size_t file_prd_off; TYPE_1__* ahw; struct firmware* fw; } ;
struct firmware {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {scalar_t__ fw_type; } ;

/* Variables and functions */
 size_t QLCNIC_BIOS_VERSION_OFFSET ; 
 scalar_t__ QLCNIC_UNIFIED_ROMIMAGE ; 
 int QLCNIC_UNI_BIOS_VERSION_OFF ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 qlcnic_get_bios_version(struct qlcnic_adapter *adapter)
{
	const struct firmware *fw = adapter->fw;
	u32 bios_ver, prd_off = adapter->file_prd_off;
	u8 *version_offset;
	__le32 temp;

	if (adapter->ahw->fw_type != QLCNIC_UNIFIED_ROMIMAGE) {
		version_offset = (u8 *)&fw->data[QLCNIC_BIOS_VERSION_OFFSET];
		return le32_to_cpu(*(__le32 *)version_offset);
	}

	temp = *((__le32 *)(&fw->data[prd_off]) + QLCNIC_UNI_BIOS_VERSION_OFF);
	bios_ver = le32_to_cpu(temp);

	return (bios_ver << 16) + ((bios_ver >> 8) & 0xff00) + (bios_ver >> 24);
}