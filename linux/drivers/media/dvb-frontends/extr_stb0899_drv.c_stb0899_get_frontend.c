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
struct stb0899_internal {int /*<<< orphan*/  freq; int /*<<< orphan*/  srate; } ;
struct stb0899_state {int /*<<< orphan*/  verbose; struct stb0899_internal internal; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  frequency; int /*<<< orphan*/  symbol_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int stb0899_get_frontend(struct dvb_frontend *fe,
				struct dtv_frontend_properties *p)
{
	struct stb0899_state *state		= fe->demodulator_priv;
	struct stb0899_internal *internal	= &state->internal;

	dprintk(state->verbose, FE_DEBUG, 1, "Get params");
	p->symbol_rate = internal->srate;
	p->frequency = internal->freq;

	return 0;
}