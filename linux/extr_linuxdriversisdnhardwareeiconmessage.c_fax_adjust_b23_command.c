#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_7__ {int internal_command; int command; int adjust_b_command; int adjust_b_ncci; int adjust_b_mode; int /*<<< orphan*/  number; int /*<<< orphan*/  appl; int /*<<< orphan*/  adjust_b_state; int /*<<< orphan*/  B1_facilities; int /*<<< orphan*/  adjust_b_facilities; int /*<<< orphan*/ * adjust_b_parms_msg; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
 int ADJUST_B_MODE_ASSIGN_L23 ; 
 int ADJUST_B_MODE_REMOVE_L23 ; 
 int /*<<< orphan*/  ADJUST_B_START ; 
 int CONFIRM ; 
#define  FAX_ADJUST_B23_COMMAND_1 129 
#define  FAX_ADJUST_B23_COMMAND_2 128 
 scalar_t__ FILE_ ; 
 int GOOD ; 
 int /*<<< orphan*/  N_CONNECT ; 
 int /*<<< orphan*/  UnMapId (int) ; 
 int _CONNECT_B3_R ; 
 int adjust_b_process (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  nl_req_ncci (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plci_nl_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  send_req (TYPE_1__*) ; 
 int /*<<< orphan*/  sendf (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void fax_adjust_b23_command(dword Id, PLCI *plci, byte Rc)
{
	word Info;
	word internal_command;

	dbug(1, dprintf("[%06lx] %s,%d: fax_adjust_b23_command %02x %04x",
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
		plci->adjust_b_command = FAX_ADJUST_B23_COMMAND_1;
		plci->adjust_b_ncci = (word)(Id >> 16);
		plci->adjust_b_mode = ADJUST_B_MODE_REMOVE_L23 | ADJUST_B_MODE_ASSIGN_L23;
		plci->adjust_b_state = ADJUST_B_START;
		dbug(1, dprintf("[%06lx] %s,%d: FAX adjust B23...",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		/* fall through */
	case FAX_ADJUST_B23_COMMAND_1:
		Info = adjust_b_process(Id, plci, Rc);
		if (Info != GOOD)
		{
			dbug(1, dprintf("[%06lx] %s,%d: FAX adjust failed",
					UnMapId(Id), (char *)(FILE_), __LINE__));
			break;
		}
		if (plci->internal_command)
			return;
		/* fall through */
	case FAX_ADJUST_B23_COMMAND_2:
		if (plci_nl_busy(plci))
		{
			plci->internal_command = FAX_ADJUST_B23_COMMAND_2;
			return;
		}
		plci->command = _CONNECT_B3_R;
		nl_req_ncci(plci, N_CONNECT, 0);
		send_req(plci);
		return;
	}
	sendf(plci->appl, _CONNECT_B3_R | CONFIRM, Id, plci->number, "w", Info);
}