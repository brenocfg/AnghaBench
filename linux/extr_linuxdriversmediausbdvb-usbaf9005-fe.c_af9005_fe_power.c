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
typedef  int u8 ;
struct dvb_frontend {struct af9005_fe_state* demodulator_priv; } ;
struct af9005_fe_state {int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int af9005_send_command (int /*<<< orphan*/ ,int,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deb_info (char*,char*) ; 

__attribute__((used)) static int af9005_fe_power(struct dvb_frontend *fe, int on)
{
	struct af9005_fe_state *state = fe->demodulator_priv;
	u8 temp = on;
	int ret;
	deb_info("power %s tuner\n", on ? "on" : "off");
	ret = af9005_send_command(state->d, 0x03, &temp, 1, NULL, 0);
	return ret;
}