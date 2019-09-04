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
typedef  void* word ;
struct TYPE_4__ {int min_digit_duration; int min_gap_duration; int /*<<< orphan*/  state; int /*<<< orphan*/  indication_state_ack; } ;
struct TYPE_5__ {TYPE_1__ recv; } ;
typedef  TYPE_2__ t_capidtmf_state ;
typedef  int dword ;

/* Variables and functions */
 int /*<<< orphan*/  CAPIDTMF_RECV_INDICATION_DIGIT ; 
 int /*<<< orphan*/  CAPIDTMF_RECV_STATE_DTMF_ACTIVE ; 
 int CAPIDTMF_RECV_TIME_GRANULARITY ; 

void capidtmf_recv_enable(t_capidtmf_state *p_state, word min_digit_duration, word min_gap_duration)
{
	p_state->recv.indication_state_ack &= CAPIDTMF_RECV_INDICATION_DIGIT;
	p_state->recv.min_digit_duration = (word)(((((dword) min_digit_duration) * 8) +
						   ((dword)(CAPIDTMF_RECV_TIME_GRANULARITY / 2))) / ((dword) CAPIDTMF_RECV_TIME_GRANULARITY));
	if (p_state->recv.min_digit_duration <= 1)
		p_state->recv.min_digit_duration = 1;
	else
		(p_state->recv.min_digit_duration)--;
	p_state->recv.min_gap_duration =
		(word)((((dword) min_gap_duration) * 8) / ((dword) CAPIDTMF_RECV_TIME_GRANULARITY));
	if (p_state->recv.min_gap_duration <= 1)
		p_state->recv.min_gap_duration = 1;
	else
		(p_state->recv.min_gap_duration)--;
	p_state->recv.state |= CAPIDTMF_RECV_STATE_DTMF_ACTIVE;
}