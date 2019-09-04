#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int dword ;
typedef  char byte ;
struct TYPE_5__ {int /*<<< orphan*/  Id; } ;
struct TYPE_6__ {int internal_command; int adjust_b_command; int adjust_b_ncci; int adjust_b_mode; int /*<<< orphan*/  appl; int /*<<< orphan*/  adjust_b_state; int /*<<< orphan*/  B1_facilities; int /*<<< orphan*/  adjust_b_facilities; int /*<<< orphan*/ * adjust_b_parms_msg; int /*<<< orphan*/  command; TYPE_1__ NL; } ;
typedef  TYPE_2__ PLCI ;

/* Variables and functions */
 int ADJUST_B_MODE_REMOVE_L23 ; 
 int ADJUST_B_MODE_SAVE ; 
 int /*<<< orphan*/  ADJUST_B_START ; 
 scalar_t__ FILE_ ; 
 int GOOD ; 
#define  HOLD_SAVE_COMMAND_1 128 
 int /*<<< orphan*/  UnMapId (int) ; 
 int /*<<< orphan*/  _FACILITY_I ; 
 int adjust_b_process (int,TYPE_2__*,char) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  sendf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int,char*) ; 

__attribute__((used)) static void hold_save_command(dword Id, PLCI *plci, byte Rc)
{
	byte SS_Ind[] = "\x05\x02\x00\x02\x00\x00"; /* Hold_Ind struct*/
	word Info;
	word internal_command;

	dbug(1, dprintf("[%06lx] %s,%d: hold_save_command %02x %04x",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->internal_command));

	Info = GOOD;
	internal_command = plci->internal_command;
	plci->internal_command = 0;
	switch (internal_command)
	{
	default:
		if (!plci->NL.Id)
			break;
		plci->command = 0;
		plci->adjust_b_parms_msg = NULL;
		plci->adjust_b_facilities = plci->B1_facilities;
		plci->adjust_b_command = HOLD_SAVE_COMMAND_1;
		plci->adjust_b_ncci = (word)(Id >> 16);
		plci->adjust_b_mode = ADJUST_B_MODE_SAVE | ADJUST_B_MODE_REMOVE_L23;
		plci->adjust_b_state = ADJUST_B_START;
		dbug(1, dprintf("[%06lx] %s,%d: HOLD save...",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		/* fall through */
	case HOLD_SAVE_COMMAND_1:
		Info = adjust_b_process(Id, plci, Rc);
		if (Info != GOOD)
		{
			dbug(1, dprintf("[%06lx] %s,%d: HOLD save failed",
					UnMapId(Id), (char *)(FILE_), __LINE__));
			break;
		}
		if (plci->internal_command)
			return;
	}
	sendf(plci->appl, _FACILITY_I, Id & 0xffffL, 0, "ws", 3, SS_Ind);
}