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
struct sps30_state {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  SPS30_RESET ; 
 int /*<<< orphan*/  SPS30_STOP_MEAS ; 
 int /*<<< orphan*/  msleep (int) ; 
 int sps30_do_cmd (struct sps30_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sps30_do_cmd_reset(struct sps30_state *state)
{
	int ret;

	ret = sps30_do_cmd(state, SPS30_RESET, NULL, 0);
	msleep(300);
	/*
	 * Power-on-reset causes sensor to produce some glitch on i2c bus and
	 * some controllers end up in error state. Recover simply by placing
	 * some data on the bus, for example STOP_MEAS command, which
	 * is NOP in this case.
	 */
	sps30_do_cmd(state, SPS30_STOP_MEAS, NULL, 0);
	state->state = RESET;

	return ret;
}