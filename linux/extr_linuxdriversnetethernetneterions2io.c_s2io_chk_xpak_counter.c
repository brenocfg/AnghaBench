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
typedef  int u64 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_DBG ; 

__attribute__((used)) static void s2io_chk_xpak_counter(u64 *counter, u64 * regs_stat, u32 index,
				  u16 flag, u16 type)
{
	u64 mask = 0x3;
	u64 val64;
	int i;
	for (i = 0; i < index; i++)
		mask = mask << 0x2;

	if (flag > 0) {
		*counter = *counter + 1;
		val64 = *regs_stat & mask;
		val64 = val64 >> (index * 0x2);
		val64 = val64 + 1;
		if (val64 == 3) {
			switch (type) {
			case 1:
				DBG_PRINT(ERR_DBG,
					  "Take Xframe NIC out of service.\n");
				DBG_PRINT(ERR_DBG,
"Excessive temperatures may result in premature transceiver failure.\n");
				break;
			case 2:
				DBG_PRINT(ERR_DBG,
					  "Take Xframe NIC out of service.\n");
				DBG_PRINT(ERR_DBG,
"Excessive bias currents may indicate imminent laser diode failure.\n");
				break;
			case 3:
				DBG_PRINT(ERR_DBG,
					  "Take Xframe NIC out of service.\n");
				DBG_PRINT(ERR_DBG,
"Excessive laser output power may saturate far-end receiver.\n");
				break;
			default:
				DBG_PRINT(ERR_DBG,
					  "Incorrect XPAK Alarm type\n");
			}
			val64 = 0x0;
		}
		val64 = val64 << (index * 0x2);
		*regs_stat = (*regs_stat & (~mask)) | (val64);

	} else {
		*regs_stat = *regs_stat & (~mask);
	}
}