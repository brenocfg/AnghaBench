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
typedef  int u32 ;
struct tg3 {scalar_t__* fw_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_APE ; 
 int /*<<< orphan*/  ENABLE_ASF ; 
 int /*<<< orphan*/  NO_NVRAM ; 
 int TG3_EEPROM_MAGIC ; 
 int TG3_EEPROM_MAGIC_FW ; 
 int TG3_EEPROM_MAGIC_FW_MSK ; 
 int TG3_EEPROM_MAGIC_HW ; 
 int TG3_EEPROM_MAGIC_HW_MSK ; 
 int TG3_VER_SIZE ; 
 int /*<<< orphan*/  strcat (scalar_t__*,char*) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_nvram_read (struct tg3*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tg3_probe_ncsi (struct tg3*) ; 
 int /*<<< orphan*/  tg3_read_bc_ver (struct tg3*) ; 
 int /*<<< orphan*/  tg3_read_dash_ver (struct tg3*) ; 
 int /*<<< orphan*/  tg3_read_hwsb_ver (struct tg3*) ; 
 int /*<<< orphan*/  tg3_read_mgmtfw_ver (struct tg3*) ; 
 int /*<<< orphan*/  tg3_read_otp_ver (struct tg3*) ; 
 int /*<<< orphan*/  tg3_read_sb_ver (struct tg3*,int) ; 

__attribute__((used)) static void tg3_read_fw_ver(struct tg3 *tp)
{
	u32 val;
	bool vpd_vers = false;

	if (tp->fw_ver[0] != 0)
		vpd_vers = true;

	if (tg3_flag(tp, NO_NVRAM)) {
		strcat(tp->fw_ver, "sb");
		tg3_read_otp_ver(tp);
		return;
	}

	if (tg3_nvram_read(tp, 0, &val))
		return;

	if (val == TG3_EEPROM_MAGIC)
		tg3_read_bc_ver(tp);
	else if ((val & TG3_EEPROM_MAGIC_FW_MSK) == TG3_EEPROM_MAGIC_FW)
		tg3_read_sb_ver(tp, val);
	else if ((val & TG3_EEPROM_MAGIC_HW_MSK) == TG3_EEPROM_MAGIC_HW)
		tg3_read_hwsb_ver(tp);

	if (tg3_flag(tp, ENABLE_ASF)) {
		if (tg3_flag(tp, ENABLE_APE)) {
			tg3_probe_ncsi(tp);
			if (!vpd_vers)
				tg3_read_dash_ver(tp);
		} else if (!vpd_vers) {
			tg3_read_mgmtfw_ver(tp);
		}
	}

	tp->fw_ver[TG3_VER_SIZE - 1] = 0;
}