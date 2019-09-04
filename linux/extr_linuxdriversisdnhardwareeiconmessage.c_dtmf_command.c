#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int dword ;
typedef  int byte ;
struct TYPE_11__ {TYPE_1__* parms; } ;
struct TYPE_12__ {int internal_command; int dtmf_cmd; int B1_facilities; int dtmf_rec_active; int /*<<< orphan*/  number; int /*<<< orphan*/  appl; int /*<<< orphan*/  dtmf_send_requests; TYPE_2__ saved_msg; int /*<<< orphan*/ * dtmf_msg_number_queue; int /*<<< orphan*/  dtmf_parameter_length; int /*<<< orphan*/  tone_last_indication_code; int /*<<< orphan*/  dtmf_send_pause_ms; int /*<<< orphan*/  dtmf_send_pulse_ms; int /*<<< orphan*/  dtmf_rec_pause_ms; int /*<<< orphan*/  dtmf_rec_pulse_ms; } ;
struct TYPE_10__ {int /*<<< orphan*/  length; int /*<<< orphan*/ * info; } ;
typedef  TYPE_3__ PLCI ;

/* Variables and functions */
 int B1_FACILITY_DTMFR ; 
 int B1_FACILITY_DTMFX ; 
 int CONFIRM ; 
#define  DTMF_COMMAND_1 139 
#define  DTMF_COMMAND_2 138 
#define  DTMF_COMMAND_3 137 
#define  DTMF_DIGITS_SEND 136 
#define  DTMF_LISTEN_MF_START 135 
#define  DTMF_LISTEN_MF_STOP 134 
#define  DTMF_LISTEN_START 133 
#define  DTMF_LISTEN_STOP 132 
#define  DTMF_LISTEN_TONE_START 131 
#define  DTMF_LISTEN_TONE_STOP 130 
#define  DTMF_SEND_MF 129 
#define  DTMF_SEND_TONE 128 
 int /*<<< orphan*/  DTMF_SIGNAL_NO_TONE ; 
 int /*<<< orphan*/  DTMF_SUCCESS ; 
 scalar_t__ FILE_ ; 
 int GOOD ; 
 int OK ; 
 int OK_FC ; 
 int /*<<< orphan*/  PUT_WORD (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELECTOR_DTMF ; 
 int /*<<< orphan*/  UnMapId (int) ; 
 int _FACILITY_NOT_SUPPORTED ; 
 int _FACILITY_R ; 
 int /*<<< orphan*/  adjust_b1_resource (int,TYPE_3__*,int /*<<< orphan*/ *,int,int const) ; 
 int adjust_b_process (int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dtmf_enable_receiver (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dtmf_send_digits (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plci_nl_busy (TYPE_3__*) ; 
 int /*<<< orphan*/  sendf (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void dtmf_command(dword Id, PLCI *plci, byte Rc)
{
	word internal_command, Info;
	byte mask;
	byte result[4];

	dbug(1, dprintf("[%06lx] %s,%d: dtmf_command %02x %04x %04x %d %d %d %d",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->internal_command,
			plci->dtmf_cmd, plci->dtmf_rec_pulse_ms, plci->dtmf_rec_pause_ms,
			plci->dtmf_send_pulse_ms, plci->dtmf_send_pause_ms));

	Info = GOOD;
	result[0] = 2;
	PUT_WORD(&result[1], DTMF_SUCCESS);
	internal_command = plci->internal_command;
	plci->internal_command = 0;
	mask = 0x01;
	switch (plci->dtmf_cmd)
	{

	case DTMF_LISTEN_TONE_START:
		mask <<= 1; /* fall through */
	case DTMF_LISTEN_MF_START:
		mask <<= 1; /* fall through */

	case DTMF_LISTEN_START:
		switch (internal_command)
		{
		default:
			adjust_b1_resource(Id, plci, NULL, (word)(plci->B1_facilities |
								  B1_FACILITY_DTMFR), DTMF_COMMAND_1);
			/* fall through */
		case DTMF_COMMAND_1:
			if (adjust_b_process(Id, plci, Rc) != GOOD)
			{
				dbug(1, dprintf("[%06lx] %s,%d: Load DTMF failed",
						UnMapId(Id), (char *)(FILE_), __LINE__));
				Info = _FACILITY_NOT_SUPPORTED;
				break;
			}
			if (plci->internal_command)
				return;
			/* fall through */
		case DTMF_COMMAND_2:
			if (plci_nl_busy(plci))
			{
				plci->internal_command = DTMF_COMMAND_2;
				return;
			}
			plci->internal_command = DTMF_COMMAND_3;
			dtmf_enable_receiver(plci, (byte)(plci->dtmf_rec_active | mask));
			return;
		case DTMF_COMMAND_3:
			if ((Rc != OK) && (Rc != OK_FC))
			{
				dbug(1, dprintf("[%06lx] %s,%d: Enable DTMF receiver failed %02x",
						UnMapId(Id), (char *)(FILE_), __LINE__, Rc));
				Info = _FACILITY_NOT_SUPPORTED;
				break;
			}

			plci->tone_last_indication_code = DTMF_SIGNAL_NO_TONE;

			plci->dtmf_rec_active |= mask;
			break;
		}
		break;


	case DTMF_LISTEN_TONE_STOP:
		mask <<= 1; /* fall through */
	case DTMF_LISTEN_MF_STOP:
		mask <<= 1; /* fall through */

	case DTMF_LISTEN_STOP:
		switch (internal_command)
		{
		default:
			plci->dtmf_rec_active &= ~mask;
			if (plci->dtmf_rec_active)
				break;
/*
  case DTMF_COMMAND_1:
  if (plci->dtmf_rec_active)
  {
  if (plci_nl_busy (plci))
  {
  plci->internal_command = DTMF_COMMAND_1;
  return;
  }
  plci->dtmf_rec_active &= ~mask;
  plci->internal_command = DTMF_COMMAND_2;
  dtmf_enable_receiver (plci, false);
  return;
  }
  Rc = OK;
  case DTMF_COMMAND_2:
  if ((Rc != OK) && (Rc != OK_FC))
  {
  dbug (1, dprintf("[%06lx] %s,%d: Disable DTMF receiver failed %02x",
  UnMapId (Id), (char far *)(FILE_), __LINE__, Rc));
  Info = _FACILITY_NOT_SUPPORTED;
  break;
  }
*/
			adjust_b1_resource(Id, plci, NULL, (word)(plci->B1_facilities &
								  ~(B1_FACILITY_DTMFX | B1_FACILITY_DTMFR)), DTMF_COMMAND_3);
			/* fall through */
		case DTMF_COMMAND_3:
			if (adjust_b_process(Id, plci, Rc) != GOOD)
			{
				dbug(1, dprintf("[%06lx] %s,%d: Unload DTMF failed",
						UnMapId(Id), (char *)(FILE_), __LINE__));
				Info = _FACILITY_NOT_SUPPORTED;
				break;
			}
			if (plci->internal_command)
				return;
			break;
		}
		break;


	case DTMF_SEND_TONE:
		mask <<= 1; /* fall through */
	case DTMF_SEND_MF:
		mask <<= 1; /* fall through */

	case DTMF_DIGITS_SEND:
		switch (internal_command)
		{
		default:
			adjust_b1_resource(Id, plci, NULL, (word)(plci->B1_facilities |
								  ((plci->dtmf_parameter_length != 0) ? B1_FACILITY_DTMFX | B1_FACILITY_DTMFR : B1_FACILITY_DTMFX)),
					   DTMF_COMMAND_1);
			/* fall through */
		case DTMF_COMMAND_1:
			if (adjust_b_process(Id, plci, Rc) != GOOD)
			{
				dbug(1, dprintf("[%06lx] %s,%d: Load DTMF failed",
						UnMapId(Id), (char *)(FILE_), __LINE__));
				Info = _FACILITY_NOT_SUPPORTED;
				break;
			}
			if (plci->internal_command)
				return;
			/* fall through */
		case DTMF_COMMAND_2:
			if (plci_nl_busy(plci))
			{
				plci->internal_command = DTMF_COMMAND_2;
				return;
			}
			plci->dtmf_msg_number_queue[(plci->dtmf_send_requests)++] = plci->number;
			plci->internal_command = DTMF_COMMAND_3;
			dtmf_send_digits(plci, &plci->saved_msg.parms[3].info[1], plci->saved_msg.parms[3].length);
			return;
		case DTMF_COMMAND_3:
			if ((Rc != OK) && (Rc != OK_FC))
			{
				dbug(1, dprintf("[%06lx] %s,%d: Send DTMF digits failed %02x",
						UnMapId(Id), (char *)(FILE_), __LINE__, Rc));
				if (plci->dtmf_send_requests != 0)
					(plci->dtmf_send_requests)--;
				Info = _FACILITY_NOT_SUPPORTED;
				break;
			}
			return;
		}
		break;
	}
	sendf(plci->appl, _FACILITY_R | CONFIRM, Id & 0xffffL, plci->number,
	      "wws", Info, SELECTOR_DTMF, result);
}