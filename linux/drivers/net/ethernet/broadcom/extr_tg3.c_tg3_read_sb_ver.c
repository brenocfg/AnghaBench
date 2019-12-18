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
struct tg3 {char* fw_ver; } ;

/* Variables and functions */
 int TG3_EEPROM_SB_EDH_BLD_MASK ; 
 int TG3_EEPROM_SB_EDH_BLD_SHFT ; 
 int TG3_EEPROM_SB_EDH_MAJ_MASK ; 
 int TG3_EEPROM_SB_EDH_MAJ_SHFT ; 
 int TG3_EEPROM_SB_EDH_MIN_MASK ; 
 int TG3_EEPROM_SB_F1R0_EDH_OFF ; 
 int TG3_EEPROM_SB_F1R2_EDH_OFF ; 
 int TG3_EEPROM_SB_F1R3_EDH_OFF ; 
 int TG3_EEPROM_SB_F1R4_EDH_OFF ; 
 int TG3_EEPROM_SB_F1R5_EDH_OFF ; 
 int TG3_EEPROM_SB_F1R6_EDH_OFF ; 
 int TG3_EEPROM_SB_FORMAT_1 ; 
 int TG3_EEPROM_SB_FORMAT_MASK ; 
#define  TG3_EEPROM_SB_REVISION_0 133 
#define  TG3_EEPROM_SB_REVISION_2 132 
#define  TG3_EEPROM_SB_REVISION_3 131 
#define  TG3_EEPROM_SB_REVISION_4 130 
#define  TG3_EEPROM_SB_REVISION_5 129 
#define  TG3_EEPROM_SB_REVISION_6 128 
 int TG3_EEPROM_SB_REVISION_MASK ; 
 int TG3_VER_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 
 scalar_t__ tg3_nvram_read (struct tg3*,int,int*) ; 

__attribute__((used)) static void tg3_read_sb_ver(struct tg3 *tp, u32 val)
{
	u32 offset, major, minor, build;

	strncat(tp->fw_ver, "sb", TG3_VER_SIZE - strlen(tp->fw_ver) - 1);

	if ((val & TG3_EEPROM_SB_FORMAT_MASK) != TG3_EEPROM_SB_FORMAT_1)
		return;

	switch (val & TG3_EEPROM_SB_REVISION_MASK) {
	case TG3_EEPROM_SB_REVISION_0:
		offset = TG3_EEPROM_SB_F1R0_EDH_OFF;
		break;
	case TG3_EEPROM_SB_REVISION_2:
		offset = TG3_EEPROM_SB_F1R2_EDH_OFF;
		break;
	case TG3_EEPROM_SB_REVISION_3:
		offset = TG3_EEPROM_SB_F1R3_EDH_OFF;
		break;
	case TG3_EEPROM_SB_REVISION_4:
		offset = TG3_EEPROM_SB_F1R4_EDH_OFF;
		break;
	case TG3_EEPROM_SB_REVISION_5:
		offset = TG3_EEPROM_SB_F1R5_EDH_OFF;
		break;
	case TG3_EEPROM_SB_REVISION_6:
		offset = TG3_EEPROM_SB_F1R6_EDH_OFF;
		break;
	default:
		return;
	}

	if (tg3_nvram_read(tp, offset, &val))
		return;

	build = (val & TG3_EEPROM_SB_EDH_BLD_MASK) >>
		TG3_EEPROM_SB_EDH_BLD_SHFT;
	major = (val & TG3_EEPROM_SB_EDH_MAJ_MASK) >>
		TG3_EEPROM_SB_EDH_MAJ_SHFT;
	minor =  val & TG3_EEPROM_SB_EDH_MIN_MASK;

	if (minor > 99 || build > 26)
		return;

	offset = strlen(tp->fw_ver);
	snprintf(&tp->fw_ver[offset], TG3_VER_SIZE - offset,
		 " v%d.%02d", major, minor);

	if (build > 0) {
		offset = strlen(tp->fw_ver);
		if (offset < TG3_VER_SIZE - 1)
			tp->fw_ver[offset] = 'a' + build - 1;
	}
}