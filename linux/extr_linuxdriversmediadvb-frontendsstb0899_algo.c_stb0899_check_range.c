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
struct stb0899_params {int freq; } ;
struct stb0899_internal {int srch_range; int freq; int derot_freq; int mclk; int status; } ;
struct stb0899_state {int /*<<< orphan*/  verbose; struct stb0899_params params; struct stb0899_internal internal; } ;
typedef  enum stb0899_status { ____Placeholder_stb0899_status } stb0899_status ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
 int OUTOFRANGE ; 
 int RANGEOK ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static enum stb0899_status stb0899_check_range(struct stb0899_state *state)
{
	struct stb0899_internal *internal = &state->internal;
	struct stb0899_params *params = &state->params;

	int range_offst, tp_freq;

	range_offst = internal->srch_range / 2000;
	tp_freq = internal->freq - (internal->derot_freq * internal->mclk) / 1000;

	if ((tp_freq >= params->freq - range_offst) && (tp_freq <= params->freq + range_offst)) {
		internal->status = RANGEOK;
		dprintk(state->verbose, FE_DEBUG, 1, "----> RANGEOK !");
	} else {
		internal->status = OUTOFRANGE;
		dprintk(state->verbose, FE_DEBUG, 1, "----> OUT OF RANGE !");
	}

	return internal->status;
}