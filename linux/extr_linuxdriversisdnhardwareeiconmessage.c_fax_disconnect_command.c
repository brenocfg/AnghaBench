#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_3__ {int internal_command; int /*<<< orphan*/  command; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
#define  FAX_DISCONNECT_COMMAND_1 130 
#define  FAX_DISCONNECT_COMMAND_2 129 
#define  FAX_DISCONNECT_COMMAND_3 128 
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  OK ; 
 int /*<<< orphan*/  OK_FC ; 
 int /*<<< orphan*/  UnMapId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void fax_disconnect_command(dword Id, PLCI *plci, byte Rc)
{
	word internal_command;

	dbug(1, dprintf("[%06lx] %s,%d: fax_disconnect_command %02x %04x",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->internal_command));

	internal_command = plci->internal_command;
	plci->internal_command = 0;
	switch (internal_command)
	{
	default:
		plci->command = 0;
		plci->internal_command = FAX_DISCONNECT_COMMAND_1;
		return;
	case FAX_DISCONNECT_COMMAND_1:
	case FAX_DISCONNECT_COMMAND_2:
	case FAX_DISCONNECT_COMMAND_3:
		if ((Rc != OK) && (Rc != OK_FC) && (Rc != 0))
		{
			dbug(1, dprintf("[%06lx] %s,%d: FAX disconnect EDATA failed %02x",
					UnMapId(Id), (char *)(FILE_), __LINE__, Rc));
			break;
		}
		if (Rc == OK)
		{
			if ((internal_command == FAX_DISCONNECT_COMMAND_1)
			    || (internal_command == FAX_DISCONNECT_COMMAND_2))
			{
				plci->internal_command = FAX_DISCONNECT_COMMAND_2;
			}
		}
		else if (Rc == 0)
		{
			if (internal_command == FAX_DISCONNECT_COMMAND_1)
				plci->internal_command = FAX_DISCONNECT_COMMAND_3;
		}
		return;
	}
}