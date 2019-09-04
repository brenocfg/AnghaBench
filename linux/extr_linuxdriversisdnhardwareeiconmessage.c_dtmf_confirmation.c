#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int dword ;
typedef  int byte ;
struct TYPE_3__ {scalar_t__ dtmf_send_requests; int /*<<< orphan*/ * dtmf_msg_number_queue; int /*<<< orphan*/  appl; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
 int CONFIRM ; 
 int /*<<< orphan*/  DTMF_SUCCESS ; 
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  GOOD ; 
 int /*<<< orphan*/  PUT_WORD (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELECTOR_DTMF ; 
 int /*<<< orphan*/  UnMapId (int) ; 
 int _FACILITY_R ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sendf (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void dtmf_confirmation(dword Id, PLCI *plci)
{
	word i;
	byte result[4];

	dbug(1, dprintf("[%06lx] %s,%d: dtmf_confirmation",
			UnMapId(Id), (char *)(FILE_), __LINE__));

	result[0] = 2;
	PUT_WORD(&result[1], DTMF_SUCCESS);
	if (plci->dtmf_send_requests != 0)
	{
		sendf(plci->appl, _FACILITY_R | CONFIRM, Id & 0xffffL, plci->dtmf_msg_number_queue[0],
		      "wws", GOOD, SELECTOR_DTMF, result);
		(plci->dtmf_send_requests)--;
		for (i = 0; i < plci->dtmf_send_requests; i++)
			plci->dtmf_msg_number_queue[i] = plci->dtmf_msg_number_queue[i + 1];
	}
}