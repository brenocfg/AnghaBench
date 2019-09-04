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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABSPOINTER_COMMAND ; 
 int /*<<< orphan*/  ABSPOINTER_STATUS ; 
 int /*<<< orphan*/  VMMOUSE_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  VMMOUSE_CMD_DISABLE ; 
 int VMMOUSE_ERROR ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*) ; 

__attribute__((used)) static void vmmouse_disable(struct psmouse *psmouse)
{
	u32 status;
	u32 dummy1, dummy2, dummy3, dummy4;

	VMMOUSE_CMD(ABSPOINTER_COMMAND, VMMOUSE_CMD_DISABLE,
		    dummy1, dummy2, dummy3, dummy4);

	VMMOUSE_CMD(ABSPOINTER_STATUS, 0,
		    status, dummy1, dummy2, dummy3);

	if ((status & VMMOUSE_ERROR) != VMMOUSE_ERROR)
		psmouse_warn(psmouse, "failed to disable vmmouse device\n");
}