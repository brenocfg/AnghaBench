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
struct dvb_frontend {struct dvb_dummy_fe_state* demodulator_priv; } ;
struct dvb_dummy_fe_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dvb_dummy_fe_state*) ; 

__attribute__((used)) static void dvb_dummy_fe_release(struct dvb_frontend* fe)
{
	struct dvb_dummy_fe_state* state = fe->demodulator_priv;
	kfree(state);
}