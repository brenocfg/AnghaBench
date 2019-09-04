#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_4__ {int internal_command; int adjust_b_command; int adjust_b_ncci; int adjust_b_mode; int /*<<< orphan*/  appl; int /*<<< orphan*/  adjust_b_state; int /*<<< orphan*/  B1_facilities; int /*<<< orphan*/  adjust_b_facilities; int /*<<< orphan*/ * adjust_b_parms_msg; int /*<<< orphan*/  command; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
 int ADJUST_B_MODE_ASSIGN_L23 ; 
 int ADJUST_B_MODE_CONNECT ; 
 int ADJUST_B_MODE_REMOVE_L23 ; 
 int /*<<< orphan*/  ADJUST_B_START ; 
 scalar_t__ FILE_ ; 
 int GOOD ; 
#define  RESET_B3_COMMAND_1 128 
 int /*<<< orphan*/  UnMapId (int) ; 
 int /*<<< orphan*/  _RESET_B3_I ; 
 int adjust_b_process (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  sendf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void reset_b3_command(dword Id, PLCI *plci, byte Rc)
{
	word Info;
	word internal_command;

	dbug(1, dprintf("[%06lx] %s,%d: reset_b3_command %02x %04x",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->internal_command));

	Info = GOOD;
	internal_command = plci->internal_command;
	plci->internal_command = 0;
	switch (internal_command)
	{
	default:
		plci->command = 0;
		plci->adjust_b_parms_msg = NULL;
		plci->adjust_b_facilities = plci->B1_facilities;
		plci->adjust_b_command = RESET_B3_COMMAND_1;
		plci->adjust_b_ncci = (word)(Id >> 16);
		plci->adjust_b_mode = ADJUST_B_MODE_REMOVE_L23 | ADJUST_B_MODE_ASSIGN_L23 | ADJUST_B_MODE_CONNECT;
		plci->adjust_b_state = ADJUST_B_START;
		dbug(1, dprintf("[%06lx] %s,%d: Reset B3...",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		/* fall through */
	case RESET_B3_COMMAND_1:
		Info = adjust_b_process(Id, plci, Rc);
		if (Info != GOOD)
		{
			dbug(1, dprintf("[%06lx] %s,%d: Reset failed",
					UnMapId(Id), (char *)(FILE_), __LINE__));
			break;
		}
		if (plci->internal_command)
			return;
		break;
	}
/*  sendf (plci->appl, _RESET_B3_R | CONFIRM, Id, plci->number, "w", Info);*/
	sendf(plci->appl, _RESET_B3_I, Id, 0, "s", "");
}