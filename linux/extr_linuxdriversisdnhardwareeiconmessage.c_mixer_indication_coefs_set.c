#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int dword ;
typedef  int byte ;
struct TYPE_5__ {int appl_flags; } ;
struct TYPE_4__ {size_t li_plci_b_read_pos; size_t li_plci_b_req_pos; int* li_plci_b_queue; TYPE_2__* appl; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
 int APPL_FLAG_OLD_LI_SPEC ; 
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  LI_IND_CONNECT_ACTIVE ; 
 int /*<<< orphan*/  LI_IND_DISCONNECT ; 
 int LI_PLCI_B_DISC_FLAG ; 
 int LI_PLCI_B_FLAG_MASK ; 
 int LI_PLCI_B_LAST_FLAG ; 
 int LI_PLCI_B_QUEUE_ENTRIES ; 
 int LI_PLCI_B_SKIP_FLAG ; 
 int /*<<< orphan*/  PUT_DWORD (int*,int) ; 
 int /*<<< orphan*/  PUT_WORD (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELECTOR_LINE_INTERCONNECT ; 
 int /*<<< orphan*/  UnMapId (int) ; 
 int /*<<< orphan*/  _FACILITY_I ; 
 int /*<<< orphan*/  _LI_USER_INITIATED ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sendf (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void mixer_indication_coefs_set(dword Id, PLCI *plci)
{
	dword d;
	byte result[12];

	dbug(1, dprintf("[%06lx] %s,%d: mixer_indication_coefs_set",
			UnMapId(Id), (char *)(FILE_), __LINE__));

	if (plci->li_plci_b_read_pos != plci->li_plci_b_req_pos)
	{
		do
		{
			d = plci->li_plci_b_queue[plci->li_plci_b_read_pos];
			if (!(d & LI_PLCI_B_SKIP_FLAG))
			{
				if (plci->appl->appl_flags & APPL_FLAG_OLD_LI_SPEC)
				{
					if (d & LI_PLCI_B_DISC_FLAG)
					{
						result[0] = 5;
						PUT_WORD(&result[1], LI_IND_DISCONNECT);
						result[3] = 2;
						PUT_WORD(&result[4], _LI_USER_INITIATED);
					}
					else
					{
						result[0] = 7;
						PUT_WORD(&result[1], LI_IND_CONNECT_ACTIVE);
						result[3] = 4;
						PUT_DWORD(&result[4], d & ~LI_PLCI_B_FLAG_MASK);
					}
				}
				else
				{
					if (d & LI_PLCI_B_DISC_FLAG)
					{
						result[0] = 9;
						PUT_WORD(&result[1], LI_IND_DISCONNECT);
						result[3] = 6;
						PUT_DWORD(&result[4], d & ~LI_PLCI_B_FLAG_MASK);
						PUT_WORD(&result[8], _LI_USER_INITIATED);
					}
					else
					{
						result[0] = 7;
						PUT_WORD(&result[1], LI_IND_CONNECT_ACTIVE);
						result[3] = 4;
						PUT_DWORD(&result[4], d & ~LI_PLCI_B_FLAG_MASK);
					}
				}
				sendf(plci->appl, _FACILITY_I, Id & 0xffffL, 0,
				      "ws", SELECTOR_LINE_INTERCONNECT, result);
			}
			plci->li_plci_b_read_pos = (plci->li_plci_b_read_pos == LI_PLCI_B_QUEUE_ENTRIES - 1) ?
				0 : plci->li_plci_b_read_pos + 1;
		} while (!(d & LI_PLCI_B_LAST_FLAG) && (plci->li_plci_b_read_pos != plci->li_plci_b_req_pos));
	}
}