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
struct psmouse {int pktcnt; int* packet; } ;

/* Variables and functions */

__attribute__((used)) static bool alps_is_valid_package_ss4_v2(struct psmouse *psmouse)
{
	if (psmouse->pktcnt == 4 && ((psmouse->packet[3] & 0x08) != 0x08))
		return false;
	if (psmouse->pktcnt == 6 && ((psmouse->packet[5] & 0x10) != 0x0))
		return false;
	return true;
}