#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct dib3000mc_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  dib3000mc_set_timing (struct dib3000mc_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib3000mc_write_word (struct dib3000mc_state*,int,int) ; 

__attribute__((used)) static int dib3000mc_set_bandwidth(struct dib3000mc_state *state, u32 bw)
{
	u16 bw_cfg[6] = { 0 };
	u16 imp_bw_cfg[3] = { 0 };
	u16 reg;

/* settings here are for 27.7MHz */
	switch (bw) {
		case 8000:
			bw_cfg[0] = 0x0019; bw_cfg[1] = 0x5c30; bw_cfg[2] = 0x0054; bw_cfg[3] = 0x88a0; bw_cfg[4] = 0x01a6; bw_cfg[5] = 0xab20;
			imp_bw_cfg[0] = 0x04db; imp_bw_cfg[1] = 0x00db; imp_bw_cfg[2] = 0x00b7;
			break;

		case 7000:
			bw_cfg[0] = 0x001c; bw_cfg[1] = 0xfba5; bw_cfg[2] = 0x0060; bw_cfg[3] = 0x9c25; bw_cfg[4] = 0x01e3; bw_cfg[5] = 0x0cb7;
			imp_bw_cfg[0] = 0x04c0; imp_bw_cfg[1] = 0x00c0; imp_bw_cfg[2] = 0x00a0;
			break;

		case 6000:
			bw_cfg[0] = 0x0021; bw_cfg[1] = 0xd040; bw_cfg[2] = 0x0070; bw_cfg[3] = 0xb62b; bw_cfg[4] = 0x0233; bw_cfg[5] = 0x8ed5;
			imp_bw_cfg[0] = 0x04a5; imp_bw_cfg[1] = 0x00a5; imp_bw_cfg[2] = 0x0089;
			break;

		case 5000:
			bw_cfg[0] = 0x0028; bw_cfg[1] = 0x9380; bw_cfg[2] = 0x0087; bw_cfg[3] = 0x4100; bw_cfg[4] = 0x02a4; bw_cfg[5] = 0x4500;
			imp_bw_cfg[0] = 0x0489; imp_bw_cfg[1] = 0x0089; imp_bw_cfg[2] = 0x0072;
			break;

		default: return -EINVAL;
	}

	for (reg = 6; reg < 12; reg++)
		dib3000mc_write_word(state, reg, bw_cfg[reg - 6]);
	dib3000mc_write_word(state, 12, 0x0000);
	dib3000mc_write_word(state, 13, 0x03e8);
	dib3000mc_write_word(state, 14, 0x0000);
	dib3000mc_write_word(state, 15, 0x03f2);
	dib3000mc_write_word(state, 16, 0x0001);
	dib3000mc_write_word(state, 17, 0xb0d0);
	// P_sec_len
	dib3000mc_write_word(state, 18, 0x0393);
	dib3000mc_write_word(state, 19, 0x8700);

	for (reg = 55; reg < 58; reg++)
		dib3000mc_write_word(state, reg, imp_bw_cfg[reg - 55]);

	// Timing configuration
	dib3000mc_set_timing(state, TRANSMISSION_MODE_2K, bw, 0);

	return 0;
}