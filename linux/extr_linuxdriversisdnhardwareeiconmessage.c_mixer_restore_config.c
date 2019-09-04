#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_11__ {TYPE_1__* plci; } ;
struct TYPE_10__ {int li_base; int manufacturer_features; } ;
struct TYPE_9__ {int adjust_b_state; int B1_facilities; int li_bchannel_id; int /*<<< orphan*/  internal_command; int /*<<< orphan*/  adjust_b_command; TYPE_2__* adapter; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
#define  ADJUST_B_RESTORE_MIXER_1 134 
#define  ADJUST_B_RESTORE_MIXER_2 133 
#define  ADJUST_B_RESTORE_MIXER_3 132 
#define  ADJUST_B_RESTORE_MIXER_4 131 
#define  ADJUST_B_RESTORE_MIXER_5 130 
#define  ADJUST_B_RESTORE_MIXER_6 129 
#define  ADJUST_B_RESTORE_MIXER_7 128 
 int B1_FACILITY_MIXER ; 
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  GOOD ; 
 int MANUFACTURER_FEATURE_XCONNECT ; 
 int /*<<< orphan*/  OK ; 
 int /*<<< orphan*/  OK_FC ; 
 int /*<<< orphan*/  UnMapId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FACILITY_NOT_SUPPORTED ; 
 int /*<<< orphan*/  _WRONG_STATE ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 TYPE_8__* li_config_table ; 
 int /*<<< orphan*/  plci_nl_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  xconnect_query_addresses (TYPE_1__*) ; 
 int /*<<< orphan*/  xconnect_write_coefs (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xconnect_write_coefs_process (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static word mixer_restore_config(dword Id, PLCI *plci, byte Rc)
{
	DIVA_CAPI_ADAPTER *a;
	word Info;

	dbug(1, dprintf("[%06lx] %s,%d: mixer_restore_config %02x %d",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->adjust_b_state));

	Info = GOOD;
	a = plci->adapter;
	if ((plci->B1_facilities & B1_FACILITY_MIXER)
	    && (plci->li_bchannel_id != 0)
	    && (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci == plci))
	{
		switch (plci->adjust_b_state)
		{
		case ADJUST_B_RESTORE_MIXER_1:
			if (a->manufacturer_features & MANUFACTURER_FEATURE_XCONNECT)
			{
				plci->internal_command = plci->adjust_b_command;
				if (plci_nl_busy(plci))
				{
					plci->adjust_b_state = ADJUST_B_RESTORE_MIXER_1;
					break;
				}
				xconnect_query_addresses(plci);
				plci->adjust_b_state = ADJUST_B_RESTORE_MIXER_2;
				break;
			}
			plci->adjust_b_state = ADJUST_B_RESTORE_MIXER_5;
			Rc = OK;
			/* fall through */
		case ADJUST_B_RESTORE_MIXER_2:
		case ADJUST_B_RESTORE_MIXER_3:
		case ADJUST_B_RESTORE_MIXER_4:
			if ((Rc != OK) && (Rc != OK_FC) && (Rc != 0))
			{
				dbug(1, dprintf("[%06lx] %s,%d: Adjust B query addresses failed %02x",
						UnMapId(Id), (char *)(FILE_), __LINE__, Rc));
				Info = _WRONG_STATE;
				break;
			}
			if (Rc == OK)
			{
				if (plci->adjust_b_state == ADJUST_B_RESTORE_MIXER_2)
					plci->adjust_b_state = ADJUST_B_RESTORE_MIXER_3;
				else if (plci->adjust_b_state == ADJUST_B_RESTORE_MIXER_4)
					plci->adjust_b_state = ADJUST_B_RESTORE_MIXER_5;
			}
			else if (Rc == 0)
			{
				if (plci->adjust_b_state == ADJUST_B_RESTORE_MIXER_2)
					plci->adjust_b_state = ADJUST_B_RESTORE_MIXER_4;
				else if (plci->adjust_b_state == ADJUST_B_RESTORE_MIXER_3)
					plci->adjust_b_state = ADJUST_B_RESTORE_MIXER_5;
			}
			if (plci->adjust_b_state != ADJUST_B_RESTORE_MIXER_5)
			{
				plci->internal_command = plci->adjust_b_command;
				break;
			}
			/* fall through */
		case ADJUST_B_RESTORE_MIXER_5:
			xconnect_write_coefs(plci, plci->adjust_b_command);
			plci->adjust_b_state = ADJUST_B_RESTORE_MIXER_6;
			Rc = OK;
			/* fall through */
		case ADJUST_B_RESTORE_MIXER_6:
			if (!xconnect_write_coefs_process(Id, plci, Rc))
			{
				dbug(1, dprintf("[%06lx] %s,%d: Write mixer coefs failed",
						UnMapId(Id), (char *)(FILE_), __LINE__));
				Info = _FACILITY_NOT_SUPPORTED;
				break;
			}
			if (plci->internal_command)
				break;
			plci->adjust_b_state = ADJUST_B_RESTORE_MIXER_7;
		case ADJUST_B_RESTORE_MIXER_7:
			break;
		}
	}
	return (Info);
}