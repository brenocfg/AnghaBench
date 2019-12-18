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
struct psmouse {int /*<<< orphan*/  packet; int /*<<< orphan*/  pktsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  psmouse_printk (int /*<<< orphan*/ ,struct psmouse*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elantech_packet_dump(struct psmouse *psmouse)
{
	psmouse_printk(KERN_DEBUG, psmouse, "PS/2 packet [%*ph]\n",
		       psmouse->pktsize, psmouse->packet);
}