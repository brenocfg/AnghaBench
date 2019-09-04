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
struct bnx2 {int flags; int bus_speed_mhz; } ;

/* Variables and functions */
 int BNX2_FLAG_PCIE ; 
 int BNX2_FLAG_PCIX ; 
 int BNX2_FLAG_PCI_32BIT ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static char *
bnx2_bus_string(struct bnx2 *bp, char *str)
{
	char *s = str;

	if (bp->flags & BNX2_FLAG_PCIE) {
		s += sprintf(s, "PCI Express");
	} else {
		s += sprintf(s, "PCI");
		if (bp->flags & BNX2_FLAG_PCIX)
			s += sprintf(s, "-X");
		if (bp->flags & BNX2_FLAG_PCI_32BIT)
			s += sprintf(s, " 32-bit");
		else
			s += sprintf(s, " 64-bit");
		s += sprintf(s, " %dMHz", bp->bus_speed_mhz);
	}
	return str;
}