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
typedef  int /*<<< orphan*/  word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_4__ {int adjust_b_state; int B1_facilities; scalar_t__ dtmf_parameter_length; int /*<<< orphan*/  sig_req; int /*<<< orphan*/  adjust_b_command; int /*<<< orphan*/  internal_command; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
#define  ADJUST_B_RESTORE_DTMF_PARAMETER_1 129 
#define  ADJUST_B_RESTORE_DTMF_PARAMETER_2 128 
 int B1_FACILITY_DTMFR ; 
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  GOOD ; 
 int /*<<< orphan*/  OK ; 
 int /*<<< orphan*/  OK_FC ; 
 int /*<<< orphan*/  UnMapId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _WRONG_STATE ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dtmf_parameter_write (TYPE_1__*) ; 

__attribute__((used)) static word dtmf_parameter_restore_config(dword Id, PLCI *plci, byte Rc)
{
	word Info;

	dbug(1, dprintf("[%06lx] %s,%d: dtmf_parameter_restore_config %02x %d",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->adjust_b_state));

	Info = GOOD;
	if ((plci->B1_facilities & B1_FACILITY_DTMFR)
	    && (plci->dtmf_parameter_length != 0))
	{
		switch (plci->adjust_b_state)
		{
		case ADJUST_B_RESTORE_DTMF_PARAMETER_1:
			plci->internal_command = plci->adjust_b_command;
			if (plci->sig_req)
			{
				plci->adjust_b_state = ADJUST_B_RESTORE_DTMF_PARAMETER_1;
				break;
			}
			dtmf_parameter_write(plci);
			plci->adjust_b_state = ADJUST_B_RESTORE_DTMF_PARAMETER_2;
			break;
		case ADJUST_B_RESTORE_DTMF_PARAMETER_2:
			if ((Rc != OK) && (Rc != OK_FC))
			{
				dbug(1, dprintf("[%06lx] %s,%d: Restore DTMF parameters failed %02x",
						UnMapId(Id), (char *)(FILE_), __LINE__, Rc));
				Info = _WRONG_STATE;
				break;
			}
			break;
		}
	}
	return (Info);
}