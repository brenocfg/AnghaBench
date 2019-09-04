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
struct sii9234 {int state; } ;
typedef  enum sii9234_state { ____Placeholder_sii9234_state } sii9234_state ;

/* Variables and functions */
 int /*<<< orphan*/  CBUS_MSC_REQ_ABORT_REASON_REG ; 
 int SET_HPD_DOWNSTREAM ; 
 int ST_FAILURE ; 
 int cbus_readb (struct sii9234*,int /*<<< orphan*/ ) ; 
 scalar_t__ sii9234_clear_error (struct sii9234*) ; 
 int /*<<< orphan*/  sii9234_tmds_control (struct sii9234*,int) ; 

__attribute__((used)) static enum sii9234_state sii9234_hpd_change(struct sii9234 *ctx)
{
	int value;

	value = cbus_readb(ctx, CBUS_MSC_REQ_ABORT_REASON_REG);
	if (sii9234_clear_error(ctx))
		return ST_FAILURE;

	if (value & SET_HPD_DOWNSTREAM) {
		/* Downstream HPD High, Enable TMDS */
		sii9234_tmds_control(ctx, true);
	} else {
		/* Downstream HPD Low, Disable TMDS */
		sii9234_tmds_control(ctx, false);
	}

	return ctx->state;
}