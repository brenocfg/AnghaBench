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
struct stv {int dummy; } ;
struct dvb_frontend {struct stv* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stop (struct stv*) ; 

__attribute__((used)) static int sleep(struct dvb_frontend *fe)
{
	struct stv *state = fe->demodulator_priv;

	stop(state);
	return 0;
}