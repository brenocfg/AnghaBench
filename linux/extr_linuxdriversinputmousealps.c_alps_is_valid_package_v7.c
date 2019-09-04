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

__attribute__((used)) static bool alps_is_valid_package_v7(struct psmouse *psmouse)
{
	switch (psmouse->pktcnt) {
	case 3:
		return (psmouse->packet[2] & 0x40) == 0x40;
	case 4:
		return (psmouse->packet[3] & 0x48) == 0x48;
	case 6:
		return (psmouse->packet[5] & 0x40) == 0x00;
	}
	return true;
}