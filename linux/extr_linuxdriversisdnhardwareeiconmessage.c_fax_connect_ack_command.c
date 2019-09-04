#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_10__ {int /*<<< orphan*/  Req; int /*<<< orphan*/  ReqCh; TYPE_1__* X; } ;
struct TYPE_9__ {int internal_command; int ncpi_state; int B3_prot; char* ncpi_buffer; int /*<<< orphan*/  appl; TYPE_4__ NL; TYPE_2__* adapter; int /*<<< orphan*/  nl_req; TYPE_1__* NData; int /*<<< orphan*/  fax_connect_info_length; int /*<<< orphan*/  fax_connect_info_buffer; int /*<<< orphan*/  command; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* request ) (TYPE_4__*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  PLength; int /*<<< orphan*/  P; } ;
typedef  TYPE_3__ PLCI ;

/* Variables and functions */
#define  FAX_CONNECT_ACK_COMMAND_1 129 
#define  FAX_CONNECT_ACK_COMMAND_2 128 
 scalar_t__ FILE_ ; 
 int NCPI_CONNECT_B3_ACT_SENT ; 
 int NCPI_VALID_CONNECT_B3_ACT ; 
 int /*<<< orphan*/  N_CONNECT_ACK ; 
 int /*<<< orphan*/  OK ; 
 int /*<<< orphan*/  OK_FC ; 
 int /*<<< orphan*/  UnMapId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CONNECT_B3_ACTIVE_I ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  plci_nl_busy (TYPE_3__*) ; 
 int /*<<< orphan*/  sendf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void fax_connect_ack_command(dword Id, PLCI *plci, byte Rc)
{
	word internal_command;

	dbug(1, dprintf("[%06lx] %s,%d: fax_connect_ack_command %02x %04x",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->internal_command));

	internal_command = plci->internal_command;
	plci->internal_command = 0;
	switch (internal_command)
	{
	default:
		plci->command = 0; /* fall through */
	case FAX_CONNECT_ACK_COMMAND_1:
		if (plci_nl_busy(plci))
		{
			plci->internal_command = FAX_CONNECT_ACK_COMMAND_1;
			return;
		}
		plci->internal_command = FAX_CONNECT_ACK_COMMAND_2;
		plci->NData[0].P = plci->fax_connect_info_buffer;
		plci->NData[0].PLength = plci->fax_connect_info_length;
		plci->NL.X = plci->NData;
		plci->NL.ReqCh = 0;
		plci->NL.Req = plci->nl_req = (byte) N_CONNECT_ACK;
		plci->adapter->request(&plci->NL);
		return;
	case FAX_CONNECT_ACK_COMMAND_2:
		if ((Rc != OK) && (Rc != OK_FC))
		{
			dbug(1, dprintf("[%06lx] %s,%d: FAX issue CONNECT ACK failed %02x",
					UnMapId(Id), (char *)(FILE_), __LINE__, Rc));
			break;
		}
	}
	if ((plci->ncpi_state & NCPI_VALID_CONNECT_B3_ACT)
	    && !(plci->ncpi_state & NCPI_CONNECT_B3_ACT_SENT))
	{
		if (plci->B3_prot == 4)
			sendf(plci->appl, _CONNECT_B3_ACTIVE_I, Id, 0, "s", "");
		else
			sendf(plci->appl, _CONNECT_B3_ACTIVE_I, Id, 0, "S", plci->ncpi_buffer);
		plci->ncpi_state |= NCPI_CONNECT_B3_ACT_SENT;
	}
}