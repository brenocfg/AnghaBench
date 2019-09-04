#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int /*<<< orphan*/  dword ;
typedef  scalar_t__ byte ;
struct TYPE_11__ {scalar_t__ character; int /*<<< orphan*/  code; } ;
struct TYPE_10__ {scalar_t__ Req; scalar_t__ ReqCh; TYPE_1__* X; } ;
struct TYPE_9__ {int Id; int dtmf_send_pulse_ms; int dtmf_send_pause_ms; TYPE_4__ NL; TYPE_2__* adapter; scalar_t__ nl_req; TYPE_1__* NData; int /*<<< orphan*/ * internal_req_buffer; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* request ) (TYPE_4__*) ;int /*<<< orphan*/  Id; } ;
struct TYPE_7__ {size_t PLength; int /*<<< orphan*/ * P; } ;
typedef  TYPE_3__ PLCI ;

/* Variables and functions */
 size_t DTMF_DIGIT_MAP_ENTRIES ; 
 int /*<<< orphan*/  DTMF_DIGIT_TONE_CODE_STAR ; 
 int /*<<< orphan*/  DTMF_UDATA_REQUEST_SEND_DIGITS ; 
 scalar_t__ FILE_ ; 
 scalar_t__ N_UDATA ; 
 int /*<<< orphan*/  PUT_WORD (int /*<<< orphan*/ *,size_t) ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,size_t) ; 
 TYPE_6__* dtmf_digit_map ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void dtmf_send_digits(PLCI *plci, byte *digit_buffer, word digit_count)
{
	word w, i;

	dbug(1, dprintf("[%06lx] %s,%d: dtmf_send_digits %d",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__, digit_count));

	plci->internal_req_buffer[0] = DTMF_UDATA_REQUEST_SEND_DIGITS;
	w = (plci->dtmf_send_pulse_ms == 0) ? 40 : plci->dtmf_send_pulse_ms;
	PUT_WORD(&plci->internal_req_buffer[1], w);
	w = (plci->dtmf_send_pause_ms == 0) ? 40 : plci->dtmf_send_pause_ms;
	PUT_WORD(&plci->internal_req_buffer[3], w);
	for (i = 0; i < digit_count; i++)
	{
		w = 0;
		while ((w < DTMF_DIGIT_MAP_ENTRIES)
		       && (digit_buffer[i] != dtmf_digit_map[w].character))
		{
			w++;
		}
		plci->internal_req_buffer[5 + i] = (w < DTMF_DIGIT_MAP_ENTRIES) ?
			dtmf_digit_map[w].code : DTMF_DIGIT_TONE_CODE_STAR;
	}
	plci->NData[0].PLength = 5 + digit_count;
	plci->NData[0].P = plci->internal_req_buffer;
	plci->NL.X = plci->NData;
	plci->NL.ReqCh = 0;
	plci->NL.Req = plci->nl_req = (byte) N_UDATA;
	plci->adapter->request(&plci->NL);
}