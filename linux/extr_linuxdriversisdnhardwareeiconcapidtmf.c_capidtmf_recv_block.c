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
typedef  scalar_t__ word ;
struct TYPE_4__ {int state; scalar_t__ cycle_counter; int current_digit_on_time; scalar_t__ current_digit_off_time; scalar_t__ min_gap_duration; size_t current_digit_value; scalar_t__ min_digit_duration; int digit_write_pos; scalar_t__ digit_read_pos; size_t* digit_buffer; int indication_state; int indication_state_ack; scalar_t__** goertzel_buffer; } ;
struct TYPE_5__ {TYPE_1__ recv; scalar_t__ ulaw; } ;
typedef  TYPE_2__ t_capidtmf_state ;
typedef  scalar_t__ dword ;
typedef  size_t byte ;

/* Variables and functions */
 scalar_t__ CAPIDTMF_LOW_GROUP_FREQUENCIES ; 
 scalar_t__ CAPIDTMF_RECV_ACCUMULATE_CYCLES ; 
 scalar_t__ CAPIDTMF_RECV_BASE_FREQUENCY_COUNT ; 
 int CAPIDTMF_RECV_DIGIT_BUFFER_SIZE ; 
 int /*<<< orphan*/  CAPIDTMF_RECV_FUNDAMENTAL_OFFSET ; 
 int CAPIDTMF_RECV_INDICATION_DIGIT ; 
 size_t CAPIDTMF_RECV_NO_DIGIT ; 
 int CAPIDTMF_RECV_STATE_DTMF_ACTIVE ; 
 int CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT ; 
 int CAPIDTMF_RECV_WINDOWED_SAMPLES ; 
 scalar_t__ DSPDTMF_RX_HIGH_EXCEEDING_LOW_DEFAULT ; 
 scalar_t__ DSPDTMF_RX_LOW_EXCEEDING_HIGH_DEFAULT ; 
 scalar_t__ DSPDTMF_RX_SENSITIVITY_HIGH_DEFAULT ; 
 scalar_t__ DSPDTMF_RX_SENSITIVITY_LOW_DEFAULT ; 
 scalar_t__ FILE_ ; 
 scalar_t__ capidtmf_dword_leading_zeroes (scalar_t__) ; 
 long* capidtmf_expand_table_alaw ; 
 long* capidtmf_expand_table_ulaw ; 
 int /*<<< orphan*/  capidtmf_goertzel_loop (scalar_t__*,int /*<<< orphan*/ *,short*,scalar_t__) ; 
 int /*<<< orphan*/  capidtmf_goertzel_result (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * capidtmf_recv_goertzel_coef_table ; 
 scalar_t__* capidtmf_recv_guard_snr_high_table ; 
 scalar_t__* capidtmf_recv_guard_snr_low_table ; 
 short* capidtmf_recv_window_function ; 
 int /*<<< orphan*/  dprintf (char*,char*,int) ; 
 int /*<<< orphan*/  trace (int /*<<< orphan*/ ) ; 

void capidtmf_recv_block(t_capidtmf_state *p_state, byte *buffer, word length)
{
	byte result_digit;
	word sample_number, cycle_counter, n, i;
	word low_peak, high_peak;
	dword lo, hi;
	byte   *p;
	short *q;
	byte goertzel_result_buffer[CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT];
	short windowed_sample_buffer[CAPIDTMF_RECV_WINDOWED_SAMPLES];


	if (p_state->recv.state & CAPIDTMF_RECV_STATE_DTMF_ACTIVE)
	{
		cycle_counter = p_state->recv.cycle_counter;
		sample_number = 0;
		while (sample_number < length)
		{
			if (cycle_counter < CAPIDTMF_RECV_ACCUMULATE_CYCLES)
			{
				if (cycle_counter == 0)
				{
					for (i = 0; i < CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT; i++)
					{
						p_state->recv.goertzel_buffer[0][i] = 0;
						p_state->recv.goertzel_buffer[1][i] = 0;
					}
				}
				n = CAPIDTMF_RECV_ACCUMULATE_CYCLES - cycle_counter;
				if (n > length - sample_number)
					n = length - sample_number;
				if (n > CAPIDTMF_RECV_WINDOWED_SAMPLES)
					n = CAPIDTMF_RECV_WINDOWED_SAMPLES;
				p = buffer + sample_number;
				q = capidtmf_recv_window_function + cycle_counter;
				if (p_state->ulaw)
				{
					for (i = 0; i < n; i++)
					{
						windowed_sample_buffer[i] =
							(short)((capidtmf_expand_table_ulaw[p[i]] * ((long)(q[i]))) >> 15);
					}
				}
				else
				{
					for (i = 0; i < n; i++)
					{
						windowed_sample_buffer[i] =
							(short)((capidtmf_expand_table_alaw[p[i]] * ((long)(q[i]))) >> 15);
					}
				}
				capidtmf_recv_goertzel_coef_table[CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT - 1] = CAPIDTMF_RECV_FUNDAMENTAL_OFFSET;
				capidtmf_goertzel_loop(p_state->recv.goertzel_buffer[0],
						       capidtmf_recv_goertzel_coef_table, windowed_sample_buffer, n);
				cycle_counter += n;
				sample_number += n;
			}
			else
			{
				capidtmf_goertzel_result(p_state->recv.goertzel_buffer[0],
							 capidtmf_recv_goertzel_coef_table);
				for (i = 0; i < CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT; i++)
				{
					lo = (dword)(p_state->recv.goertzel_buffer[0][i]);
					hi = (dword)(p_state->recv.goertzel_buffer[1][i]);
					if (hi != 0)
					{
						n = capidtmf_dword_leading_zeroes(hi);
						hi = (hi << n) | (lo >> (32 - n));
					}
					else
					{
						n = capidtmf_dword_leading_zeroes(lo);
						hi = lo << n;
						n += 32;
					}
					n = 195 - 3 * n;
					if (hi >= 0xcb300000L)
						n += 2;
					else if (hi >= 0xa1450000L)
						n++;
					goertzel_result_buffer[i] = (byte) n;
				}
				low_peak = DSPDTMF_RX_SENSITIVITY_LOW_DEFAULT;
				result_digit = CAPIDTMF_RECV_NO_DIGIT;
				for (i = 0; i < CAPIDTMF_LOW_GROUP_FREQUENCIES; i++)
				{
					if (goertzel_result_buffer[i] > low_peak)
					{
						low_peak = goertzel_result_buffer[i];
						result_digit = (byte) i;
					}
				}
				high_peak = DSPDTMF_RX_SENSITIVITY_HIGH_DEFAULT;
				n = CAPIDTMF_RECV_NO_DIGIT;
				for (i = CAPIDTMF_LOW_GROUP_FREQUENCIES; i < CAPIDTMF_RECV_BASE_FREQUENCY_COUNT; i++)
				{
					if (goertzel_result_buffer[i] > high_peak)
					{
						high_peak = goertzel_result_buffer[i];
						n = (i - CAPIDTMF_LOW_GROUP_FREQUENCIES) << 2;
					}
				}
				result_digit |= (byte) n;
				if (low_peak + DSPDTMF_RX_HIGH_EXCEEDING_LOW_DEFAULT < high_peak)
					result_digit = CAPIDTMF_RECV_NO_DIGIT;
				if (high_peak + DSPDTMF_RX_LOW_EXCEEDING_HIGH_DEFAULT < low_peak)
					result_digit = CAPIDTMF_RECV_NO_DIGIT;
				n = 0;
				for (i = 0; i < CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT; i++)
				{
					if ((((short)(low_peak - goertzel_result_buffer[i] - capidtmf_recv_guard_snr_low_table[i])) < 0)
					    || (((short)(high_peak - goertzel_result_buffer[i] - capidtmf_recv_guard_snr_high_table[i])) < 0))
					{
						n++;
					}
				}
				if (n != 2)
					result_digit = CAPIDTMF_RECV_NO_DIGIT;

				if (result_digit == CAPIDTMF_RECV_NO_DIGIT)
				{
					if (p_state->recv.current_digit_on_time != 0)
					{
						if (++(p_state->recv.current_digit_off_time) >= p_state->recv.min_gap_duration)
						{
							p_state->recv.current_digit_on_time = 0;
							p_state->recv.current_digit_off_time = 0;
						}
					}
					else
					{
						if (p_state->recv.current_digit_off_time != 0)
							(p_state->recv.current_digit_off_time)--;
					}
				}
				else
				{
					if ((p_state->recv.current_digit_on_time == 0)
					    && (p_state->recv.current_digit_off_time != 0))
					{
						(p_state->recv.current_digit_off_time)--;
					}
					else
					{
						n = p_state->recv.current_digit_off_time;
						if ((p_state->recv.current_digit_on_time != 0)
						    && (result_digit != p_state->recv.current_digit_value))
						{
							p_state->recv.current_digit_on_time = 0;
							n = 0;
						}
						p_state->recv.current_digit_value = result_digit;
						p_state->recv.current_digit_off_time = 0;
						if (p_state->recv.current_digit_on_time != 0xffff)
						{
							p_state->recv.current_digit_on_time += n + 1;
							if (p_state->recv.current_digit_on_time >= p_state->recv.min_digit_duration)
							{
								p_state->recv.current_digit_on_time = 0xffff;
								i = (p_state->recv.digit_write_pos == CAPIDTMF_RECV_DIGIT_BUFFER_SIZE - 1) ?
									0 : p_state->recv.digit_write_pos + 1;
								if (i == p_state->recv.digit_read_pos)
								{
									trace(dprintf("%s,%d: Receive digit overrun",
										      (char *)(FILE_), __LINE__));
								}
								else
								{
									p_state->recv.digit_buffer[p_state->recv.digit_write_pos] = result_digit;
									p_state->recv.digit_write_pos = i;
									p_state->recv.indication_state =
										(p_state->recv.indication_state & ~CAPIDTMF_RECV_INDICATION_DIGIT) |
										(~p_state->recv.indication_state_ack & CAPIDTMF_RECV_INDICATION_DIGIT);
								}
							}
						}
					}
				}
				cycle_counter = 0;
				sample_number++;
			}
		}
		p_state->recv.cycle_counter = cycle_counter;
	}
}