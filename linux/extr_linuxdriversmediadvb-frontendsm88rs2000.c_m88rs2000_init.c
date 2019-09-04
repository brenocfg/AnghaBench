#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct m88rs2000_state {TYPE_1__* config; } ;
struct inittab {int dummy; } ;
struct dvb_frontend {struct m88rs2000_state* demodulator_priv; } ;
struct TYPE_2__ {scalar_t__ inittab; } ;

/* Variables and functions */
 int /*<<< orphan*/  deb_info (char*) ; 
 struct inittab* m88rs2000_setup ; 
 int m88rs2000_tab_set (struct m88rs2000_state*,struct inittab*) ; 

__attribute__((used)) static int m88rs2000_init(struct dvb_frontend *fe)
{
	struct m88rs2000_state *state = fe->demodulator_priv;
	int ret;

	deb_info("m88rs2000: init chip\n");
	/* Setup frontend from shutdown/cold */
	if (state->config->inittab)
		ret = m88rs2000_tab_set(state,
				(struct inittab *)state->config->inittab);
	else
		ret = m88rs2000_tab_set(state, m88rs2000_setup);

	return ret;
}