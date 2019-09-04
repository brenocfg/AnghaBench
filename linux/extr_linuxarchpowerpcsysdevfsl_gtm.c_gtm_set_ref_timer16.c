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
typedef  int u8 ;
struct gtm_timer {int /*<<< orphan*/  gtcfr; scalar_t__ gtevr; scalar_t__ gtrfr; scalar_t__ gtcnr; int /*<<< orphan*/  gtmdr; scalar_t__ gtpsr; struct gtm* gtm; } ;
struct gtm {int clock; int /*<<< orphan*/  lock; struct gtm_timer* timers; } ;

/* Variables and functions */
 int EINVAL ; 
 int GTCFR_RST (int) ; 
 int GTCFR_STP (int) ; 
 int GTMDR_FRR ; 
 int GTMDR_ICLK_ICLK ; 
 int GTMDR_ICLK_SLGO ; 
 int GTMDR_ORI ; 
 int GTMDR_SPS (int) ; 
 int /*<<< orphan*/  clrbits8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clrsetbits_8 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clrsetbits_be16 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  out_be16 (scalar_t__,int) ; 
 int /*<<< orphan*/  setbits8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gtm_set_ref_timer16(struct gtm_timer *tmr, int frequency,
			       int reference_value, bool free_run)
{
	struct gtm *gtm = tmr->gtm;
	int num = tmr - &gtm->timers[0];
	unsigned int prescaler;
	u8 iclk = GTMDR_ICLK_ICLK;
	u8 psr;
	u8 sps;
	unsigned long flags;
	int max_prescaler = 256 * 256 * 16;

	/* CPM2 doesn't have primary prescaler */
	if (!tmr->gtpsr)
		max_prescaler /= 256;

	prescaler = gtm->clock / frequency;
	/*
	 * We have two 8 bit prescalers -- primary and secondary (psr, sps),
	 * plus "slow go" mode (clk / 16). So, total prescale value is
	 * 16 * (psr + 1) * (sps + 1). Though, for CPM2 GTMs we losing psr.
	 */
	if (prescaler > max_prescaler)
		return -EINVAL;

	if (prescaler > max_prescaler / 16) {
		iclk = GTMDR_ICLK_SLGO;
		prescaler /= 16;
	}

	if (prescaler <= 256) {
		psr = 0;
		sps = prescaler - 1;
	} else {
		psr = 256 - 1;
		sps = prescaler / 256 - 1;
	}

	spin_lock_irqsave(&gtm->lock, flags);

	/*
	 * Properly reset timers: stop, reset, set up prescalers, reference
	 * value and clear event register.
	 */
	clrsetbits_8(tmr->gtcfr, ~(GTCFR_STP(num) | GTCFR_RST(num)),
				 GTCFR_STP(num) | GTCFR_RST(num));

	setbits8(tmr->gtcfr, GTCFR_STP(num));

	if (tmr->gtpsr)
		out_be16(tmr->gtpsr, psr);
	clrsetbits_be16(tmr->gtmdr, 0xFFFF, iclk | GTMDR_SPS(sps) |
			GTMDR_ORI | (free_run ? GTMDR_FRR : 0));
	out_be16(tmr->gtcnr, 0);
	out_be16(tmr->gtrfr, reference_value);
	out_be16(tmr->gtevr, 0xFFFF);

	/* Let it be. */
	clrbits8(tmr->gtcfr, GTCFR_STP(num));

	spin_unlock_irqrestore(&gtm->lock, flags);

	return 0;
}