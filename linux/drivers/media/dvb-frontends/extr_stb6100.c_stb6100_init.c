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
struct stb6100_state {int bandwidth; int reference; } ;
struct dvb_frontend {struct stb6100_state* tuner_priv; } ;

/* Variables and functions */

__attribute__((used)) static int stb6100_init(struct dvb_frontend *fe)
{
	struct stb6100_state *state = fe->tuner_priv;
	int refclk = 27000000; /* Hz */

	/*
	 * iqsense = 1
	 * tunerstep = 125000
	 */
	state->bandwidth        = 36000000;		/* Hz	*/
	state->reference	= refclk / 1000;	/* kHz	*/

	/* Set default bandwidth. Modified, PN 13-May-10	*/
	return 0;
}