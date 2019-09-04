#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int dword ;
typedef  int byte ;
struct TYPE_8__ {int appl_flags; } ;
struct TYPE_7__ {int internal_command; int ec_cmd; int B1_facilities; TYPE_2__* appl; int /*<<< orphan*/  number; int /*<<< orphan*/  sig_req; int /*<<< orphan*/  ec_tail_length; int /*<<< orphan*/  ec_idi_options; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
 int APPL_FLAG_PRIV_EC_SPEC ; 
 int B1_FACILITY_EC ; 
 int CONFIRM ; 
#define  EC_COMMAND_1 135 
#define  EC_COMMAND_2 134 
#define  EC_COMMAND_3 133 
#define  EC_DISABLE_OPERATION 132 
#define  EC_ENABLE_OPERATION 131 
#define  EC_FREEZE_COEFFICIENTS 130 
#define  EC_RESET_COEFFICIENTS 129 
#define  EC_RESUME_COEFFICIENT_UPDATE 128 
 int EC_SUCCESS ; 
 scalar_t__ FILE_ ; 
 int GOOD ; 
 int OK ; 
 int OK_FC ; 
 int /*<<< orphan*/  PRIV_SELECTOR_ECHO_CANCELLER ; 
 int /*<<< orphan*/  PUT_WORD (int*,int) ; 
 int /*<<< orphan*/  SELECTOR_ECHO_CANCELLER ; 
 int /*<<< orphan*/  UnMapId (int) ; 
 int _FACILITY_NOT_SUPPORTED ; 
 int _FACILITY_R ; 
 int /*<<< orphan*/  adjust_b1_resource (int,TYPE_1__*,int /*<<< orphan*/ *,int,int const) ; 
 int adjust_b_process (int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ec_write_parameters (TYPE_1__*) ; 
 int /*<<< orphan*/  sendf (TYPE_2__*,int,int,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void ec_command(dword Id, PLCI *plci, byte Rc)
{
	word internal_command, Info;
	byte result[8];

	dbug(1, dprintf("[%06lx] %s,%d: ec_command %02x %04x %04x %04x %d",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->internal_command,
			plci->ec_cmd, plci->ec_idi_options, plci->ec_tail_length));

	Info = GOOD;
	if (plci->appl->appl_flags & APPL_FLAG_PRIV_EC_SPEC)
	{
		result[0] = 2;
		PUT_WORD(&result[1], EC_SUCCESS);
	}
	else
	{
		result[0] = 5;
		PUT_WORD(&result[1], plci->ec_cmd);
		result[3] = 2;
		PUT_WORD(&result[4], GOOD);
	}
	internal_command = plci->internal_command;
	plci->internal_command = 0;
	switch (plci->ec_cmd)
	{
	case EC_ENABLE_OPERATION:
	case EC_FREEZE_COEFFICIENTS:
	case EC_RESUME_COEFFICIENT_UPDATE:
	case EC_RESET_COEFFICIENTS:
		switch (internal_command)
		{
		default:
			adjust_b1_resource(Id, plci, NULL, (word)(plci->B1_facilities |
								  B1_FACILITY_EC), EC_COMMAND_1);
			/* fall through */
		case EC_COMMAND_1:
			if (adjust_b_process(Id, plci, Rc) != GOOD)
			{
				dbug(1, dprintf("[%06lx] %s,%d: Load EC failed",
						UnMapId(Id), (char *)(FILE_), __LINE__));
				Info = _FACILITY_NOT_SUPPORTED;
				break;
			}
			if (plci->internal_command)
				return;
			/* fall through */
		case EC_COMMAND_2:
			if (plci->sig_req)
			{
				plci->internal_command = EC_COMMAND_2;
				return;
			}
			plci->internal_command = EC_COMMAND_3;
			ec_write_parameters(plci);
			return;
		case EC_COMMAND_3:
			if ((Rc != OK) && (Rc != OK_FC))
			{
				dbug(1, dprintf("[%06lx] %s,%d: Enable EC failed %02x",
						UnMapId(Id), (char *)(FILE_), __LINE__, Rc));
				Info = _FACILITY_NOT_SUPPORTED;
				break;
			}
			break;
		}
		break;

	case EC_DISABLE_OPERATION:
		switch (internal_command)
		{
		default:
		case EC_COMMAND_1:
			if (plci->B1_facilities & B1_FACILITY_EC)
			{
				if (plci->sig_req)
				{
					plci->internal_command = EC_COMMAND_1;
					return;
				}
				plci->internal_command = EC_COMMAND_2;
				ec_write_parameters(plci);
				return;
			}
			Rc = OK;
			/* fall through */
		case EC_COMMAND_2:
			if ((Rc != OK) && (Rc != OK_FC))
			{
				dbug(1, dprintf("[%06lx] %s,%d: Disable EC failed %02x",
						UnMapId(Id), (char *)(FILE_), __LINE__, Rc));
				Info = _FACILITY_NOT_SUPPORTED;
				break;
			}
			adjust_b1_resource(Id, plci, NULL, (word)(plci->B1_facilities &
								  ~B1_FACILITY_EC), EC_COMMAND_3);
			/* fall through */
		case EC_COMMAND_3:
			if (adjust_b_process(Id, plci, Rc) != GOOD)
			{
				dbug(1, dprintf("[%06lx] %s,%d: Unload EC failed",
						UnMapId(Id), (char *)(FILE_), __LINE__));
				Info = _FACILITY_NOT_SUPPORTED;
				break;
			}
			if (plci->internal_command)
				return;
			break;
		}
		break;
	}
	sendf(plci->appl, _FACILITY_R | CONFIRM, Id & 0xffffL, plci->number,
	      "wws", Info, (plci->appl->appl_flags & APPL_FLAG_PRIV_EC_SPEC) ?
	      PRIV_SELECTOR_ECHO_CANCELLER : SELECTOR_ECHO_CANCELLER, result);
}