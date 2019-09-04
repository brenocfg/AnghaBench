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
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct dib0090_state {scalar_t__ tune_state; } ;

/* Variables and functions */
 scalar_t__ CT_TUNER_START ; 
 scalar_t__ CT_TUNER_STOP ; 
 int FE_CALLBACK_TIME_NEVER ; 
 int dib0090_tune (struct dvb_frontend*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dib0090_set_params(struct dvb_frontend *fe)
{
	struct dib0090_state *state = fe->tuner_priv;
	u32 ret;

	state->tune_state = CT_TUNER_START;

	do {
		ret = dib0090_tune(fe);
		if (ret == FE_CALLBACK_TIME_NEVER)
			break;

		/*
		 * Despite dib0090_tune returns time at a 0.1 ms range,
		 * the actual sleep time depends on CONFIG_HZ. The worse case
		 * is when CONFIG_HZ=100. In such case, the minimum granularity
		 * is 10ms. On some real field tests, the tuner sometimes don't
		 * lock when this timer is lower than 10ms. So, enforce a 10ms
		 * granularity and use usleep_range() instead of msleep().
		 */
		ret = 10 * (ret + 99)/100;
		usleep_range(ret * 1000, (ret + 1) * 1000);
	} while (state->tune_state != CT_TUNER_STOP);

	return 0;
}