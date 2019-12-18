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
struct tda_state {int dummy; } ;
struct dvb_frontend {struct tda_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  StandBy (struct tda_state*) ; 

__attribute__((used)) static int sleep(struct dvb_frontend *fe)
{
	struct tda_state *state = fe->tuner_priv;

	StandBy(state);
	return 0;
}