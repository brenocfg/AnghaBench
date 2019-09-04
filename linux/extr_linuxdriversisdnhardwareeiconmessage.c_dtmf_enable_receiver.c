#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int /*<<< orphan*/  dword ;
typedef  scalar_t__ byte ;
struct TYPE_9__ {scalar_t__ Req; scalar_t__ ReqCh; TYPE_1__* X; } ;
struct TYPE_8__ {int Id; int dtmf_rec_pulse_ms; int dtmf_rec_pause_ms; TYPE_4__ NL; TYPE_2__* adapter; scalar_t__ nl_req; TYPE_1__* NData; int /*<<< orphan*/ * internal_req_buffer; int /*<<< orphan*/  capidtmf_state; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* request ) (TYPE_4__*) ;int /*<<< orphan*/  Id; } ;
struct TYPE_6__ {int PLength; int /*<<< orphan*/ * P; } ;
typedef  TYPE_3__ PLCI ;

/* Variables and functions */
 int /*<<< orphan*/  DTMF_UDATA_REQUEST_DISABLE_RECEIVER ; 
 int /*<<< orphan*/  DTMF_UDATA_REQUEST_ENABLE_RECEIVER ; 
 scalar_t__ FILE_ ; 
 int INTERNAL_IND_BUFFER_SIZE ; 
 scalar_t__ N_UDATA ; 
 int /*<<< orphan*/  PUT_WORD (int /*<<< orphan*/ *,int) ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capidtmf_recv_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capidtmf_recv_enable (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void dtmf_enable_receiver(PLCI *plci, byte enable_mask)
{
	word min_digit_duration, min_gap_duration;

	dbug(1, dprintf("[%06lx] %s,%d: dtmf_enable_receiver %02x",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__, enable_mask));

	if (enable_mask != 0)
	{
		min_digit_duration = (plci->dtmf_rec_pulse_ms == 0) ? 40 : plci->dtmf_rec_pulse_ms;
		min_gap_duration = (plci->dtmf_rec_pause_ms == 0) ? 40 : plci->dtmf_rec_pause_ms;
		plci->internal_req_buffer[0] = DTMF_UDATA_REQUEST_ENABLE_RECEIVER;
		PUT_WORD(&plci->internal_req_buffer[1], min_digit_duration);
		PUT_WORD(&plci->internal_req_buffer[3], min_gap_duration);
		plci->NData[0].PLength = 5;

		PUT_WORD(&plci->internal_req_buffer[5], INTERNAL_IND_BUFFER_SIZE);
		plci->NData[0].PLength += 2;
		capidtmf_recv_enable(&(plci->capidtmf_state), min_digit_duration, min_gap_duration);

	}
	else
	{
		plci->internal_req_buffer[0] = DTMF_UDATA_REQUEST_DISABLE_RECEIVER;
		plci->NData[0].PLength = 1;

		capidtmf_recv_disable(&(plci->capidtmf_state));

	}
	plci->NData[0].P = plci->internal_req_buffer;
	plci->NL.X = plci->NData;
	plci->NL.ReqCh = 0;
	plci->NL.Req = plci->nl_req = (byte) N_UDATA;
	plci->adapter->request(&plci->NL);
}