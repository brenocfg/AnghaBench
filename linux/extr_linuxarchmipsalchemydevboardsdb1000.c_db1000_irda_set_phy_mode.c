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

/* Variables and functions */
#define  AU1000_IRDA_PHY_MODE_FIR 130 
#define  AU1000_IRDA_PHY_MODE_OFF 129 
#define  AU1000_IRDA_PHY_MODE_SIR 128 
 int /*<<< orphan*/  BCSR_RESETS ; 
 unsigned short BCSR_RESETS_FIR_SEL ; 
 unsigned short BCSR_RESETS_IRDA_MODE_FULL ; 
 unsigned short BCSR_RESETS_IRDA_MODE_MASK ; 
 unsigned short BCSR_RESETS_IRDA_MODE_OFF ; 
 int /*<<< orphan*/  bcsr_mod (int /*<<< orphan*/ ,unsigned short,unsigned short) ; 

__attribute__((used)) static void db1000_irda_set_phy_mode(int mode)
{
	unsigned short mask = BCSR_RESETS_IRDA_MODE_MASK | BCSR_RESETS_FIR_SEL;

	switch (mode) {
	case AU1000_IRDA_PHY_MODE_OFF:
		bcsr_mod(BCSR_RESETS, mask, BCSR_RESETS_IRDA_MODE_OFF);
		break;
	case AU1000_IRDA_PHY_MODE_SIR:
		bcsr_mod(BCSR_RESETS, mask, BCSR_RESETS_IRDA_MODE_FULL);
		break;
	case AU1000_IRDA_PHY_MODE_FIR:
		bcsr_mod(BCSR_RESETS, mask, BCSR_RESETS_IRDA_MODE_FULL |
					    BCSR_RESETS_FIR_SEL);
		break;
	}
}