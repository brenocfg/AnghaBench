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
 int /*<<< orphan*/  ABSPOINTER_DATA ; 
 int /*<<< orphan*/  ABSPOINTER_RESTRICT ; 
 int /*<<< orphan*/  ABSPOINTER_STATUS ; 
 int ENXIO ; 
 int /*<<< orphan*/  VMMOUSE_CMD (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int VMMOUSE_CMD_ENABLE ; 
 int VMMOUSE_CMD_REQUEST_ABSOLUTE ; 
 int VMMOUSE_RESTRICT_CPL0 ; 
 int VMMOUSE_VERSION_ID ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,...) ; 
 int /*<<< orphan*/  vmmouse_disable (struct psmouse*) ; 

__attribute__((used)) static int vmmouse_enable(struct psmouse *psmouse)
{
	u32 status, version;
	u32 dummy1, dummy2, dummy3, dummy4;

	/*
	 * Try enabling the device. If successful, we should be able to
	 * read valid version ID back from it.
	 */
	VMMOUSE_CMD(ABSPOINTER_COMMAND, VMMOUSE_CMD_ENABLE,
		    dummy1, dummy2, dummy3, dummy4);

	/*
	 * See if version ID can be retrieved.
	 */
	VMMOUSE_CMD(ABSPOINTER_STATUS, 0, status, dummy1, dummy2, dummy3);
	if ((status & 0x0000ffff) == 0) {
		psmouse_dbg(psmouse, "empty flags - assuming no device\n");
		return -ENXIO;
	}

	VMMOUSE_CMD(ABSPOINTER_DATA, 1 /* single item */,
		    version, dummy1, dummy2, dummy3);
	if (version != VMMOUSE_VERSION_ID) {
		psmouse_dbg(psmouse, "Unexpected version value: %u vs %u\n",
			    (unsigned) version, VMMOUSE_VERSION_ID);
		vmmouse_disable(psmouse);
		return -ENXIO;
	}

	/*
	 * Restrict ioport access, if possible.
	 */
	VMMOUSE_CMD(ABSPOINTER_RESTRICT, VMMOUSE_RESTRICT_CPL0,
		    dummy1, dummy2, dummy3, dummy4);

	VMMOUSE_CMD(ABSPOINTER_COMMAND, VMMOUSE_CMD_REQUEST_ABSOLUTE,
		    dummy1, dummy2, dummy3, dummy4);

	return 0;
}