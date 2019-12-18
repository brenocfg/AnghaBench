#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct rtl_fw_phy_action {size_t size; int /*<<< orphan*/ * code; } ;
struct rtl_fw {int /*<<< orphan*/  fw_name; int /*<<< orphan*/  version; struct rtl_fw_phy_action phy_action; struct firmware* fw; } ;
struct fw_info {int /*<<< orphan*/  version; int /*<<< orphan*/  fw_len; int /*<<< orphan*/  fw_start; int /*<<< orphan*/  magic; } ;
struct firmware {scalar_t__* data; size_t size; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 size_t FW_OPCODE_SIZE ; 
 int /*<<< orphan*/  RTL_VER_SIZE ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rtl_fw_format_ok(struct rtl_fw *rtl_fw)
{
	const struct firmware *fw = rtl_fw->fw;
	struct fw_info *fw_info = (struct fw_info *)fw->data;
	struct rtl_fw_phy_action *pa = &rtl_fw->phy_action;

	if (fw->size < FW_OPCODE_SIZE)
		return false;

	if (!fw_info->magic) {
		size_t i, size, start;
		u8 checksum = 0;

		if (fw->size < sizeof(*fw_info))
			return false;

		for (i = 0; i < fw->size; i++)
			checksum += fw->data[i];
		if (checksum != 0)
			return false;

		start = le32_to_cpu(fw_info->fw_start);
		if (start > fw->size)
			return false;

		size = le32_to_cpu(fw_info->fw_len);
		if (size > (fw->size - start) / FW_OPCODE_SIZE)
			return false;

		strscpy(rtl_fw->version, fw_info->version, RTL_VER_SIZE);

		pa->code = (__le32 *)(fw->data + start);
		pa->size = size;
	} else {
		if (fw->size % FW_OPCODE_SIZE)
			return false;

		strscpy(rtl_fw->version, rtl_fw->fw_name, RTL_VER_SIZE);

		pa->code = (__le32 *)fw->data;
		pa->size = fw->size / FW_OPCODE_SIZE;
	}

	return true;
}