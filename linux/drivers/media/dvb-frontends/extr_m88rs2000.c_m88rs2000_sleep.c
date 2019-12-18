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
struct m88rs2000_state {int dummy; } ;
struct dvb_frontend {struct m88rs2000_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  m88rs2000_shutdown ; 
 int m88rs2000_tab_set (struct m88rs2000_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m88rs2000_sleep(struct dvb_frontend *fe)
{
	struct m88rs2000_state *state = fe->demodulator_priv;
	int ret;
	/* Shutdown the frondend */
	ret = m88rs2000_tab_set(state, m88rs2000_shutdown);
	return ret;
}