#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct tda1004x_state {TYPE_1__* config; } ;
typedef  int /*<<< orphan*/  bandwidth_8mhz_53M ;
typedef  int /*<<< orphan*/  bandwidth_8mhz_48M ;
typedef  int /*<<< orphan*/  bandwidth_7mhz_53M ;
typedef  int /*<<< orphan*/  bandwidth_7mhz_48M ;
typedef  int /*<<< orphan*/  bandwidth_6mhz_53M ;
typedef  int /*<<< orphan*/  bandwidth_6mhz_48M ;
struct TYPE_2__ {scalar_t__ if_freq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TDA10046H_FREQ_PHY2_LSB ; 
 int /*<<< orphan*/  TDA10046H_FREQ_PHY2_MSB ; 
 int /*<<< orphan*/  TDA10046H_TIME_WREF1 ; 
 scalar_t__ TDA10046_FREQ_045 ; 
 scalar_t__ TDA10046_FREQ_052 ; 
 int /*<<< orphan*/  tda1004x_write_buf (struct tda1004x_state*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  tda1004x_write_byteI (struct tda1004x_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tda10046h_set_bandwidth(struct tda1004x_state *state,
				   u32 bandwidth)
{
	static u8 bandwidth_6mhz_53M[] = { 0x7b, 0x2e, 0x11, 0xf0, 0xd2 };
	static u8 bandwidth_7mhz_53M[] = { 0x6a, 0x02, 0x6a, 0x43, 0x9f };
	static u8 bandwidth_8mhz_53M[] = { 0x5c, 0x32, 0xc2, 0x96, 0x6d };

	static u8 bandwidth_6mhz_48M[] = { 0x70, 0x02, 0x49, 0x24, 0x92 };
	static u8 bandwidth_7mhz_48M[] = { 0x60, 0x02, 0xaa, 0xaa, 0xab };
	static u8 bandwidth_8mhz_48M[] = { 0x54, 0x03, 0x0c, 0x30, 0xc3 };
	int tda10046_clk53m;

	if ((state->config->if_freq == TDA10046_FREQ_045) ||
	    (state->config->if_freq == TDA10046_FREQ_052))
		tda10046_clk53m = 0;
	else
		tda10046_clk53m = 1;
	switch (bandwidth) {
	case 6000000:
		if (tda10046_clk53m)
			tda1004x_write_buf(state, TDA10046H_TIME_WREF1, bandwidth_6mhz_53M,
						  sizeof(bandwidth_6mhz_53M));
		else
			tda1004x_write_buf(state, TDA10046H_TIME_WREF1, bandwidth_6mhz_48M,
						  sizeof(bandwidth_6mhz_48M));
		if (state->config->if_freq == TDA10046_FREQ_045) {
			tda1004x_write_byteI(state, TDA10046H_FREQ_PHY2_MSB, 0x0a);
			tda1004x_write_byteI(state, TDA10046H_FREQ_PHY2_LSB, 0xab);
		}
		break;

	case 7000000:
		if (tda10046_clk53m)
			tda1004x_write_buf(state, TDA10046H_TIME_WREF1, bandwidth_7mhz_53M,
						  sizeof(bandwidth_7mhz_53M));
		else
			tda1004x_write_buf(state, TDA10046H_TIME_WREF1, bandwidth_7mhz_48M,
						  sizeof(bandwidth_7mhz_48M));
		if (state->config->if_freq == TDA10046_FREQ_045) {
			tda1004x_write_byteI(state, TDA10046H_FREQ_PHY2_MSB, 0x0c);
			tda1004x_write_byteI(state, TDA10046H_FREQ_PHY2_LSB, 0x00);
		}
		break;

	case 8000000:
		if (tda10046_clk53m)
			tda1004x_write_buf(state, TDA10046H_TIME_WREF1, bandwidth_8mhz_53M,
						  sizeof(bandwidth_8mhz_53M));
		else
			tda1004x_write_buf(state, TDA10046H_TIME_WREF1, bandwidth_8mhz_48M,
						  sizeof(bandwidth_8mhz_48M));
		if (state->config->if_freq == TDA10046_FREQ_045) {
			tda1004x_write_byteI(state, TDA10046H_FREQ_PHY2_MSB, 0x0d);
			tda1004x_write_byteI(state, TDA10046H_FREQ_PHY2_LSB, 0x55);
		}
		break;

	default:
		return -EINVAL;
	}

	return 0;
}