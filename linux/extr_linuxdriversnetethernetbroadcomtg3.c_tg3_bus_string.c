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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRC_MISC_CFG ; 
 int GRC_MISC_CFG_BOARD_ID_5704CIOBE ; 
 int GRC_MISC_CFG_BOARD_ID_MASK ; 
 int /*<<< orphan*/  PCIX_MODE ; 
 int /*<<< orphan*/  PCI_32BIT ; 
 int /*<<< orphan*/  PCI_EXPRESS ; 
 int /*<<< orphan*/  PCI_HIGH_SPEED ; 
 int /*<<< orphan*/  TG3PCI_CLOCK_CTRL ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int tr32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *tg3_bus_string(struct tg3 *tp, char *str)
{
	if (tg3_flag(tp, PCI_EXPRESS)) {
		strcpy(str, "PCI Express");
		return str;
	} else if (tg3_flag(tp, PCIX_MODE)) {
		u32 clock_ctrl = tr32(TG3PCI_CLOCK_CTRL) & 0x1f;

		strcpy(str, "PCIX:");

		if ((clock_ctrl == 7) ||
		    ((tr32(GRC_MISC_CFG) & GRC_MISC_CFG_BOARD_ID_MASK) ==
		     GRC_MISC_CFG_BOARD_ID_5704CIOBE))
			strcat(str, "133MHz");
		else if (clock_ctrl == 0)
			strcat(str, "33MHz");
		else if (clock_ctrl == 2)
			strcat(str, "50MHz");
		else if (clock_ctrl == 4)
			strcat(str, "66MHz");
		else if (clock_ctrl == 6)
			strcat(str, "100MHz");
	} else {
		strcpy(str, "PCI:");
		if (tg3_flag(tp, PCI_HIGH_SPEED))
			strcat(str, "66MHz");
		else
			strcat(str, "33MHz");
	}
	if (tg3_flag(tp, PCI_32BIT))
		strcat(str, ":32-bit");
	else
		strcat(str, ":64-bit");
	return str;
}