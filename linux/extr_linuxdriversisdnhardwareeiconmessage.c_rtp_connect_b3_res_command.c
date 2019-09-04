#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_12__ {int /*<<< orphan*/  Req; int /*<<< orphan*/  ReqCh; TYPE_1__* X; } ;
struct TYPE_11__ {int internal_command; TYPE_4__ NL; TYPE_2__* adapter; int /*<<< orphan*/  nl_req; TYPE_1__* NData; int /*<<< orphan*/ * internal_req_buffer; int /*<<< orphan*/  appl; int /*<<< orphan*/  command; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* request ) (TYPE_4__*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  P; int /*<<< orphan*/  PLength; } ;
typedef  TYPE_3__ PLCI ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  N_CONNECT_ACK ; 
 int /*<<< orphan*/  N_UDATA ; 
 int /*<<< orphan*/  OK ; 
 int /*<<< orphan*/  OK_FC ; 
#define  RTP_CONNECT_B3_RES_COMMAND_1 130 
#define  RTP_CONNECT_B3_RES_COMMAND_2 129 
#define  RTP_CONNECT_B3_RES_COMMAND_3 128 
 int /*<<< orphan*/  UnMapId (int) ; 
 int /*<<< orphan*/  _CONNECT_B3_ACTIVE_I ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  nl_req_ncci (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plci_nl_busy (TYPE_3__*) ; 
 int /*<<< orphan*/  send_req (TYPE_3__*) ; 
 int /*<<< orphan*/  sendf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void rtp_connect_b3_res_command(dword Id, PLCI *plci, byte Rc)
{
	word internal_command;

	dbug(1, dprintf("[%06lx] %s,%d: rtp_connect_b3_res_command %02x %04x",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->internal_command));

	internal_command = plci->internal_command;
	plci->internal_command = 0;
	switch (internal_command)
	{
	default:
		plci->command = 0; /* fall through */
	case RTP_CONNECT_B3_RES_COMMAND_1:
		if (plci_nl_busy(plci))
		{
			plci->internal_command = RTP_CONNECT_B3_RES_COMMAND_1;
			return;
		}
		plci->internal_command = RTP_CONNECT_B3_RES_COMMAND_2;
		nl_req_ncci(plci, N_CONNECT_ACK, (byte)(Id >> 16));
		send_req(plci);
		return;
	case RTP_CONNECT_B3_RES_COMMAND_2:
		if ((Rc != OK) && (Rc != OK_FC))
		{
			dbug(1, dprintf("[%06lx] %s,%d: RTP setting connect resp info failed %02x",
					UnMapId(Id), (char *)(FILE_), __LINE__, Rc));
			break;
		}
		if (plci_nl_busy(plci))
		{
			plci->internal_command = RTP_CONNECT_B3_RES_COMMAND_2;
			return;
		}
		sendf(plci->appl, _CONNECT_B3_ACTIVE_I, Id, 0, "s", "");
		plci->internal_command = RTP_CONNECT_B3_RES_COMMAND_3;
		plci->NData[0].PLength = plci->internal_req_buffer[0];
		plci->NData[0].P = plci->internal_req_buffer + 1;
		plci->NL.X = plci->NData;
		plci->NL.ReqCh = 0;
		plci->NL.Req = plci->nl_req = (byte) N_UDATA;
		plci->adapter->request(&plci->NL);
		return;
	case RTP_CONNECT_B3_RES_COMMAND_3:
		return;
	}
}