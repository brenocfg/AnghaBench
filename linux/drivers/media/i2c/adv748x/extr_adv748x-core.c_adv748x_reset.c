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
typedef  int /*<<< orphan*/  u8 ;
struct adv748x_state {int /*<<< orphan*/  txb; int /*<<< orphan*/  txa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_CP_CLMP_POS ; 
 int /*<<< orphan*/  ADV748X_CP_CLMP_POS_DIS_AUTO ; 
 int /*<<< orphan*/  ADV748X_IO_10 ; 
 int /*<<< orphan*/  ADV748X_IO_10_CSI1_EN ; 
 int /*<<< orphan*/  ADV748X_IO_10_CSI4_EN ; 
 int /*<<< orphan*/  ADV748X_IO_PD ; 
 int /*<<< orphan*/  ADV748X_IO_PD_RX_EN ; 
 int /*<<< orphan*/  adv748x_init_afe ; 
 int /*<<< orphan*/  adv748x_init_hdmi ; 
 int adv748x_set_slave_addresses (struct adv748x_state*) ; 
 int adv748x_sw_reset (struct adv748x_state*) ; 
 int /*<<< orphan*/  adv748x_tx_power (int /*<<< orphan*/ *,int) ; 
 int adv748x_write_regs (struct adv748x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_clrset (struct adv748x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write (struct adv748x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_tx_enabled (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv748x_reset(struct adv748x_state *state)
{
	int ret;
	u8 regval = 0;

	ret = adv748x_sw_reset(state);
	if (ret < 0)
		return ret;

	ret = adv748x_set_slave_addresses(state);
	if (ret < 0)
		return ret;

	/* Initialize CP and AFE cores. */
	ret = adv748x_write_regs(state, adv748x_init_hdmi);
	if (ret)
		return ret;

	ret = adv748x_write_regs(state, adv748x_init_afe);
	if (ret)
		return ret;

	/* Reset TXA and TXB */
	adv748x_tx_power(&state->txa, 1);
	adv748x_tx_power(&state->txa, 0);
	adv748x_tx_power(&state->txb, 1);
	adv748x_tx_power(&state->txb, 0);

	/* Disable chip powerdown & Enable HDMI Rx block */
	io_write(state, ADV748X_IO_PD, ADV748X_IO_PD_RX_EN);

	/* Conditionally enable TXa and TXb. */
	if (is_tx_enabled(&state->txa))
		regval |= ADV748X_IO_10_CSI4_EN;
	if (is_tx_enabled(&state->txb))
		regval |= ADV748X_IO_10_CSI1_EN;
	io_write(state, ADV748X_IO_10, regval);

	/* Use vid_std and v_freq as freerun resolution for CP */
	cp_clrset(state, ADV748X_CP_CLMP_POS, ADV748X_CP_CLMP_POS_DIS_AUTO,
					      ADV748X_CP_CLMP_POS_DIS_AUTO);

	return 0;
}