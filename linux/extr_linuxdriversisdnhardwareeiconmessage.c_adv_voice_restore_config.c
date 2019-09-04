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
typedef  int /*<<< orphan*/  word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_6__ {TYPE_1__* AdvSignalPLCI; } ;
struct TYPE_5__ {int adjust_b_state; int B1_facilities; scalar_t__ tel; int /*<<< orphan*/  sig_req; int /*<<< orphan*/  adjust_b_command; int /*<<< orphan*/  internal_command; TYPE_2__* adapter; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
#define  ADJUST_B_RESTORE_VOICE_1 129 
#define  ADJUST_B_RESTORE_VOICE_2 128 
 scalar_t__ ADV_VOICE ; 
 int /*<<< orphan*/  ADV_VOICE_WRITE_UPDATE ; 
 int B1_FACILITY_VOICE ; 
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  GOOD ; 
 int /*<<< orphan*/  OK ; 
 int /*<<< orphan*/  OK_FC ; 
 int /*<<< orphan*/  UnMapId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _WRONG_STATE ; 
 int /*<<< orphan*/  adv_voice_write_coefs (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static word adv_voice_restore_config(dword Id, PLCI *plci, byte Rc)
{
	DIVA_CAPI_ADAPTER *a;
	word Info;

	dbug(1, dprintf("[%06lx] %s,%d: adv_voice_restore_config %02x %d",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->adjust_b_state));

	Info = GOOD;
	a = plci->adapter;
	if ((plci->B1_facilities & B1_FACILITY_VOICE)
	    && (plci->tel == ADV_VOICE) && (plci == a->AdvSignalPLCI))
	{
		switch (plci->adjust_b_state)
		{
		case ADJUST_B_RESTORE_VOICE_1:
			plci->internal_command = plci->adjust_b_command;
			if (plci->sig_req)
			{
				plci->adjust_b_state = ADJUST_B_RESTORE_VOICE_1;
				break;
			}
			adv_voice_write_coefs(plci, ADV_VOICE_WRITE_UPDATE);
			plci->adjust_b_state = ADJUST_B_RESTORE_VOICE_2;
			break;
		case ADJUST_B_RESTORE_VOICE_2:
			if ((Rc != OK) && (Rc != OK_FC))
			{
				dbug(1, dprintf("[%06lx] %s,%d: Restore voice config failed %02x",
						UnMapId(Id), (char *)(FILE_), __LINE__, Rc));
				Info = _WRONG_STATE;
				break;
			}
			break;
		}
	}
	return (Info);
}