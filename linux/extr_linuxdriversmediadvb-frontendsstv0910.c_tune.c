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
struct stv {int /*<<< orphan*/  tune_time; } ;
struct dvb_frontend {struct stv* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int FE_HAS_LOCK ; 
 unsigned int HZ ; 
 int /*<<< orphan*/  jiffies ; 
 int read_status (struct dvb_frontend*,int*) ; 
 int set_parameters (struct dvb_frontend*) ; 

__attribute__((used)) static int tune(struct dvb_frontend *fe, bool re_tune,
		unsigned int mode_flags,
		unsigned int *delay, enum fe_status *status)
{
	struct stv *state = fe->demodulator_priv;
	int r;

	if (re_tune) {
		r = set_parameters(fe);
		if (r)
			return r;
		state->tune_time = jiffies;
	}

	r = read_status(fe, status);
	if (r)
		return r;

	if (*status & FE_HAS_LOCK)
		return 0;
	*delay = HZ;

	return 0;
}