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
struct adv748x_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_CP_CLMP_POS ; 
 int /*<<< orphan*/  ADV748X_CP_CLMP_POS_DIS_AUTO ; 
 int /*<<< orphan*/  ADV748X_IO_10 ; 
 int ADV748X_IO_10_CSI1_EN ; 
 int ADV748X_IO_10_CSI4_EN ; 
 int ADV748X_IO_10_PIX_OUT_EN ; 
 int /*<<< orphan*/  ADV748X_IO_PD ; 
 int ADV748X_IO_PD_RX_EN ; 
 int /*<<< orphan*/  adv748x_init_txa_4lane ; 
 int /*<<< orphan*/  adv748x_init_txb_1lane ; 
 int adv748x_set_slave_addresses (struct adv748x_state*) ; 
 int /*<<< orphan*/  adv748x_sw_reset ; 
 int /*<<< orphan*/  adv748x_txa_power (struct adv748x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv748x_txb_power (struct adv748x_state*,int /*<<< orphan*/ ) ; 
 int adv748x_write_regs (struct adv748x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_clrset (struct adv748x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write (struct adv748x_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adv748x_reset(struct adv748x_state *state)
{
	int ret;

	ret = adv748x_write_regs(state, adv748x_sw_reset);
	if (ret < 0)
		return ret;

	ret = adv748x_set_slave_addresses(state);
	if (ret < 0)
		return ret;

	/* Init and power down TXA */
	ret = adv748x_write_regs(state, adv748x_init_txa_4lane);
	if (ret)
		return ret;

	adv748x_txa_power(state, 0);

	/* Init and power down TXB */
	ret = adv748x_write_regs(state, adv748x_init_txb_1lane);
	if (ret)
		return ret;

	adv748x_txb_power(state, 0);

	/* Disable chip powerdown & Enable HDMI Rx block */
	io_write(state, ADV748X_IO_PD, ADV748X_IO_PD_RX_EN);

	/* Enable 4-lane CSI Tx & Pixel Port */
	io_write(state, ADV748X_IO_10, ADV748X_IO_10_CSI4_EN |
				       ADV748X_IO_10_CSI1_EN |
				       ADV748X_IO_10_PIX_OUT_EN);

	/* Use vid_std and v_freq as freerun resolution for CP */
	cp_clrset(state, ADV748X_CP_CLMP_POS, ADV748X_CP_CLMP_POS_DIS_AUTO,
					      ADV748X_CP_CLMP_POS_DIS_AUTO);

	return 0;
}