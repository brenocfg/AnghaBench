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
struct stv090x_state {scalar_t__ frequency; int srate; int search_range; int /*<<< orphan*/  fec; int /*<<< orphan*/  algo; int /*<<< orphan*/  search_mode; int /*<<< orphan*/  delsys; } ;
struct dtv_frontend_properties {scalar_t__ frequency; int delivery_system; int symbol_rate; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  scrambling_sequence_index; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct stv090x_state* demodulator_priv; } ;
typedef  enum dvbfe_search { ____Placeholder_dvbfe_search } dvbfe_search ;

/* Variables and functions */
 int DVBFE_ALGO_SEARCH_ERROR ; 
 int DVBFE_ALGO_SEARCH_FAILED ; 
 int DVBFE_ALGO_SEARCH_INVALID ; 
 int DVBFE_ALGO_SEARCH_SUCCESS ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  STV090x_COLD_SEARCH ; 
 int /*<<< orphan*/  STV090x_DSS ; 
 int /*<<< orphan*/  STV090x_DVBS1 ; 
 int /*<<< orphan*/  STV090x_DVBS2 ; 
 int /*<<< orphan*/  STV090x_PRERR ; 
 scalar_t__ STV090x_RANGEOK ; 
 int /*<<< orphan*/  STV090x_SEARCH_AUTO ; 
#define  SYS_DSS 130 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ stv090x_algo (struct stv090x_state*) ; 
 int /*<<< orphan*/  stv090x_set_mis (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv090x_set_pls (struct stv090x_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum dvbfe_search stv090x_search(struct dvb_frontend *fe)
{
	struct stv090x_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *props = &fe->dtv_property_cache;

	if (props->frequency == 0)
		return DVBFE_ALGO_SEARCH_INVALID;

	switch (props->delivery_system) {
	case SYS_DSS:
		state->delsys = STV090x_DSS;
		break;
	case SYS_DVBS:
		state->delsys = STV090x_DVBS1;
		break;
	case SYS_DVBS2:
		state->delsys = STV090x_DVBS2;
		break;
	default:
		return DVBFE_ALGO_SEARCH_INVALID;
	}

	state->frequency = props->frequency;
	state->srate = props->symbol_rate;
	state->search_mode = STV090x_SEARCH_AUTO;
	state->algo = STV090x_COLD_SEARCH;
	state->fec = STV090x_PRERR;
	if (state->srate > 10000000) {
		dprintk(FE_DEBUG, 1, "Search range: 10 MHz");
		state->search_range = 10000000;
	} else {
		dprintk(FE_DEBUG, 1, "Search range: 5 MHz");
		state->search_range = 5000000;
	}

	stv090x_set_pls(state, props->scrambling_sequence_index);
	stv090x_set_mis(state, props->stream_id);

	if (stv090x_algo(state) == STV090x_RANGEOK) {
		dprintk(FE_DEBUG, 1, "Search success!");
		return DVBFE_ALGO_SEARCH_SUCCESS;
	} else {
		dprintk(FE_DEBUG, 1, "Search failed!");
		return DVBFE_ALGO_SEARCH_FAILED;
	}

	return DVBFE_ALGO_SEARCH_ERROR;
}