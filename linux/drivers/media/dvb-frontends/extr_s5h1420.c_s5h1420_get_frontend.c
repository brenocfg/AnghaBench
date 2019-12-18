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
struct s5h1420_state {scalar_t__ tunedfreq; } ;
struct dvb_frontend {struct s5h1420_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  inversion; scalar_t__ frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  s5h1420_getfec (struct s5h1420_state*) ; 
 scalar_t__ s5h1420_getfreqoffset (struct s5h1420_state*) ; 
 int /*<<< orphan*/  s5h1420_getinversion (struct s5h1420_state*) ; 
 int /*<<< orphan*/  s5h1420_getsymbolrate (struct s5h1420_state*) ; 

__attribute__((used)) static int s5h1420_get_frontend(struct dvb_frontend* fe,
				struct dtv_frontend_properties *p)
{
	struct s5h1420_state* state = fe->demodulator_priv;

	p->frequency = state->tunedfreq + s5h1420_getfreqoffset(state);
	p->inversion = s5h1420_getinversion(state);
	p->symbol_rate = s5h1420_getsymbolrate(state);
	p->fec_inner = s5h1420_getfec(state);

	return 0;
}