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
typedef  scalar_t__ u64 ;
struct skl_wrpll_context {scalar_t__ min_deviation; unsigned int p; scalar_t__ dco_freq; scalar_t__ central_freq; } ;

/* Variables and functions */
 scalar_t__ SKL_DCO_MAX_NDEVIATION ; 
 scalar_t__ SKL_DCO_MAX_PDEVIATION ; 
 int abs_diff (scalar_t__,scalar_t__) ; 
 scalar_t__ div64_u64 (int,scalar_t__) ; 

__attribute__((used)) static void skl_wrpll_try_divider(struct skl_wrpll_context *ctx,
				  u64 central_freq,
				  u64 dco_freq,
				  unsigned int divider)
{
	u64 deviation;

	deviation = div64_u64(10000 * abs_diff(dco_freq, central_freq),
			      central_freq);

	/* positive deviation */
	if (dco_freq >= central_freq) {
		if (deviation < SKL_DCO_MAX_PDEVIATION &&
		    deviation < ctx->min_deviation) {
			ctx->min_deviation = deviation;
			ctx->central_freq = central_freq;
			ctx->dco_freq = dco_freq;
			ctx->p = divider;
		}
	/* negative deviation */
	} else if (deviation < SKL_DCO_MAX_NDEVIATION &&
		   deviation < ctx->min_deviation) {
		ctx->min_deviation = deviation;
		ctx->central_freq = central_freq;
		ctx->dco_freq = dco_freq;
		ctx->p = divider;
	}
}