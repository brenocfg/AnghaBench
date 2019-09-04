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
struct TYPE_4__ {int min_gap_duration; int min_digit_duration; int /*<<< orphan*/  state; scalar_t__ indication_state_ack; scalar_t__ indication_state; scalar_t__ digit_read_pos; scalar_t__ digit_write_pos; int /*<<< orphan*/  current_digit_value; scalar_t__ current_digit_off_time; scalar_t__ current_digit_on_time; scalar_t__ cycle_counter; } ;
struct TYPE_5__ {TYPE_1__ recv; } ;
typedef  TYPE_2__ t_capidtmf_state ;

/* Variables and functions */
 int /*<<< orphan*/  CAPIDTMF_RECV_NO_DIGIT ; 
 int /*<<< orphan*/  CAPIDTMF_RECV_STATE_IDLE ; 

__attribute__((used)) static void capidtmf_recv_init(t_capidtmf_state *p_state)
{
	p_state->recv.min_gap_duration = 1;
	p_state->recv.min_digit_duration = 1;

	p_state->recv.cycle_counter = 0;
	p_state->recv.current_digit_on_time = 0;
	p_state->recv.current_digit_off_time = 0;
	p_state->recv.current_digit_value = CAPIDTMF_RECV_NO_DIGIT;

	p_state->recv.digit_write_pos = 0;
	p_state->recv.digit_read_pos = 0;
	p_state->recv.indication_state = 0;
	p_state->recv.indication_state_ack = 0;
	p_state->recv.state = CAPIDTMF_RECV_STATE_IDLE;
}