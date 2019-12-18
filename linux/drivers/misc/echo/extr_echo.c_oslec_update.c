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
struct TYPE_2__ {size_t curr_pos; int /*<<< orphan*/  coeffs; scalar_t__* history; } ;
struct oslec_state {int tx; int rx; int adaption_mode; int rx_1; int rx_2; int pstates; int log2taps; int ltxacc; int ltx; int lrxacc; int lrx; int clean; int lcleanacc; int lclean; int lclean_bgacc; int lclean_bg; int shift; scalar_t__ nonupdate_dwell; int adapt; int cond_met; int taps; int clean_nlp; int cng_level; int lbgn; unsigned int cng_rndnum; int cng_filter; int lbgn_acc; int curr_pos; int /*<<< orphan*/ * fir_taps16; scalar_t__ factor; TYPE_1__ fir_state_bg; TYPE_1__ fir_state; } ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int DC_LOG2BETA ; 
 scalar_t__ DTD_HANGOVER ; 
 int ECHO_CAN_DISABLE ; 
 int ECHO_CAN_USE_ADAPTION ; 
 int ECHO_CAN_USE_CLIP ; 
 int ECHO_CAN_USE_CNG ; 
 int ECHO_CAN_USE_NLP ; 
 int ECHO_CAN_USE_RX_HPF ; 
 int MIN_RX_POWER_FOR_ADAPTION ; 
 int MIN_TX_POWER_FOR_ADAPTION ; 
 int abs (int) ; 
 int fir16 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lms_adapt_bg (struct oslec_state*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int top_bit (int) ; 

int16_t oslec_update(struct oslec_state *ec, int16_t tx, int16_t rx)
{
	int32_t echo_value;
	int clean_bg;
	int tmp;
	int tmp1;

	/*
	 * Input scaling was found be required to prevent problems when tx
	 * starts clipping.  Another possible way to handle this would be the
	 * filter coefficent scaling.
	 */

	ec->tx = tx;
	ec->rx = rx;
	tx >>= 1;
	rx >>= 1;

	/*
	 * Filter DC, 3dB point is 160Hz (I think), note 32 bit precision
	 * required otherwise values do not track down to 0. Zero at DC, Pole
	 * at (1-Beta) on real axis.  Some chip sets (like Si labs) don't
	 * need this, but something like a $10 X100P card does.  Any DC really
	 * slows down convergence.
	 *
	 * Note: removes some low frequency from the signal, this reduces the
	 * speech quality when listening to samples through headphones but may
	 * not be obvious through a telephone handset.
	 *
	 * Note that the 3dB frequency in radians is approx Beta, e.g. for Beta
	 * = 2^(-3) = 0.125, 3dB freq is 0.125 rads = 159Hz.
	 */

	if (ec->adaption_mode & ECHO_CAN_USE_RX_HPF) {
		tmp = rx << 15;

		/*
		 * Make sure the gain of the HPF is 1.0. This can still
		 * saturate a little under impulse conditions, and it might
		 * roll to 32768 and need clipping on sustained peak level
		 * signals. However, the scale of such clipping is small, and
		 * the error due to any saturation should not markedly affect
		 * the downstream processing.
		 */
		tmp -= (tmp >> 4);

		ec->rx_1 += -(ec->rx_1 >> DC_LOG2BETA) + tmp - ec->rx_2;

		/*
		 * hard limit filter to prevent clipping.  Note that at this
		 * stage rx should be limited to +/- 16383 due to right shift
		 * above
		 */
		tmp1 = ec->rx_1 >> 15;
		if (tmp1 > 16383)
			tmp1 = 16383;
		if (tmp1 < -16383)
			tmp1 = -16383;
		rx = tmp1;
		ec->rx_2 = tmp;
	}

	/* Block average of power in the filter states.  Used for
	   adaption power calculation. */

	{
		int new, old;

		/* efficient "out with the old and in with the new" algorithm so
		   we don't have to recalculate over the whole block of
		   samples. */
		new = (int)tx * (int)tx;
		old = (int)ec->fir_state.history[ec->fir_state.curr_pos] *
		    (int)ec->fir_state.history[ec->fir_state.curr_pos];
		ec->pstates +=
		    ((new - old) + (1 << (ec->log2taps - 1))) >> ec->log2taps;
		if (ec->pstates < 0)
			ec->pstates = 0;
	}

	/* Calculate short term average levels using simple single pole IIRs */

	ec->ltxacc += abs(tx) - ec->ltx;
	ec->ltx = (ec->ltxacc + (1 << 4)) >> 5;
	ec->lrxacc += abs(rx) - ec->lrx;
	ec->lrx = (ec->lrxacc + (1 << 4)) >> 5;

	/* Foreground filter */

	ec->fir_state.coeffs = ec->fir_taps16[0];
	echo_value = fir16(&ec->fir_state, tx);
	ec->clean = rx - echo_value;
	ec->lcleanacc += abs(ec->clean) - ec->lclean;
	ec->lclean = (ec->lcleanacc + (1 << 4)) >> 5;

	/* Background filter */

	echo_value = fir16(&ec->fir_state_bg, tx);
	clean_bg = rx - echo_value;
	ec->lclean_bgacc += abs(clean_bg) - ec->lclean_bg;
	ec->lclean_bg = (ec->lclean_bgacc + (1 << 4)) >> 5;

	/* Background Filter adaption */

	/* Almost always adap bg filter, just simple DT and energy
	   detection to minimise adaption in cases of strong double talk.
	   However this is not critical for the dual path algorithm.
	 */
	ec->factor = 0;
	ec->shift = 0;
	if (!ec->nonupdate_dwell) {
		int p, logp, shift;

		/* Determine:

		   f = Beta * clean_bg_rx/P ------ (1)

		   where P is the total power in the filter states.

		   The Boffins have shown that if we obey (1) we converge
		   quickly and avoid instability.

		   The correct factor f must be in Q30, as this is the fixed
		   point format required by the lms_adapt_bg() function,
		   therefore the scaled version of (1) is:

		   (2^30) * f  = (2^30) * Beta * clean_bg_rx/P
		   factor      = (2^30) * Beta * clean_bg_rx/P     ----- (2)

		   We have chosen Beta = 0.25 by experiment, so:

		   factor      = (2^30) * (2^-2) * clean_bg_rx/P

		   (30 - 2 - log2(P))
		   factor      = clean_bg_rx 2                     ----- (3)

		   To avoid a divide we approximate log2(P) as top_bit(P),
		   which returns the position of the highest non-zero bit in
		   P.  This approximation introduces an error as large as a
		   factor of 2, but the algorithm seems to handle it OK.

		   Come to think of it a divide may not be a big deal on a
		   modern DSP, so its probably worth checking out the cycles
		   for a divide versus a top_bit() implementation.
		 */

		p = MIN_TX_POWER_FOR_ADAPTION + ec->pstates;
		logp = top_bit(p) + ec->log2taps;
		shift = 30 - 2 - logp;
		ec->shift = shift;

		lms_adapt_bg(ec, clean_bg, shift);
	}

	/* very simple DTD to make sure we dont try and adapt with strong
	   near end speech */

	ec->adapt = 0;
	if ((ec->lrx > MIN_RX_POWER_FOR_ADAPTION) && (ec->lrx > ec->ltx))
		ec->nonupdate_dwell = DTD_HANGOVER;
	if (ec->nonupdate_dwell)
		ec->nonupdate_dwell--;

	/* Transfer logic */

	/* These conditions are from the dual path paper [1], I messed with
	   them a bit to improve performance. */

	if ((ec->adaption_mode & ECHO_CAN_USE_ADAPTION) &&
	    (ec->nonupdate_dwell == 0) &&
	    /* (ec->Lclean_bg < 0.875*ec->Lclean) */
	    (8 * ec->lclean_bg < 7 * ec->lclean) &&
	    /* (ec->Lclean_bg < 0.125*ec->Ltx) */
	    (8 * ec->lclean_bg < ec->ltx)) {
		if (ec->cond_met == 6) {
			/*
			 * BG filter has had better results for 6 consecutive
			 * samples
			 */
			ec->adapt = 1;
			memcpy(ec->fir_taps16[0], ec->fir_taps16[1],
			       ec->taps * sizeof(int16_t));
		} else
			ec->cond_met++;
	} else
		ec->cond_met = 0;

	/* Non-Linear Processing */

	ec->clean_nlp = ec->clean;
	if (ec->adaption_mode & ECHO_CAN_USE_NLP) {
		/*
		 * Non-linear processor - a fancy way to say "zap small
		 * signals, to avoid residual echo due to (uLaw/ALaw)
		 * non-linearity in the channel.".
		 */

		if ((16 * ec->lclean < ec->ltx)) {
			/*
			 * Our e/c has improved echo by at least 24 dB (each
			 * factor of 2 is 6dB, so 2*2*2*2=16 is the same as
			 * 6+6+6+6=24dB)
			 */
			if (ec->adaption_mode & ECHO_CAN_USE_CNG) {
				ec->cng_level = ec->lbgn;

				/*
				 * Very elementary comfort noise generation.
				 * Just random numbers rolled off very vaguely
				 * Hoth-like.  DR: This noise doesn't sound
				 * quite right to me - I suspect there are some
				 * overflow issues in the filtering as it's too
				 * "crackly".
				 * TODO: debug this, maybe just play noise at
				 * high level or look at spectrum.
				 */

				ec->cng_rndnum =
				    1664525U * ec->cng_rndnum + 1013904223U;
				ec->cng_filter =
				    ((ec->cng_rndnum & 0xFFFF) - 32768 +
				     5 * ec->cng_filter) >> 3;
				ec->clean_nlp =
				    (ec->cng_filter * ec->cng_level * 8) >> 14;

			} else if (ec->adaption_mode & ECHO_CAN_USE_CLIP) {
				/* This sounds much better than CNG */
				if (ec->clean_nlp > ec->lbgn)
					ec->clean_nlp = ec->lbgn;
				if (ec->clean_nlp < -ec->lbgn)
					ec->clean_nlp = -ec->lbgn;
			} else {
				/*
				 * just mute the residual, doesn't sound very
				 * good, used mainly in G168 tests
				 */
				ec->clean_nlp = 0;
			}
		} else {
			/*
			 * Background noise estimator.  I tried a few
			 * algorithms here without much luck.  This very simple
			 * one seems to work best, we just average the level
			 * using a slow (1 sec time const) filter if the
			 * current level is less than a (experimentally
			 * derived) constant.  This means we dont include high
			 * level signals like near end speech.  When combined
			 * with CNG or especially CLIP seems to work OK.
			 */
			if (ec->lclean < 40) {
				ec->lbgn_acc += abs(ec->clean) - ec->lbgn;
				ec->lbgn = (ec->lbgn_acc + (1 << 11)) >> 12;
			}
		}
	}

	/* Roll around the taps buffer */
	if (ec->curr_pos <= 0)
		ec->curr_pos = ec->taps;
	ec->curr_pos--;

	if (ec->adaption_mode & ECHO_CAN_DISABLE)
		ec->clean_nlp = rx;

	/* Output scaled back up again to match input scaling */

	return (int16_t) ec->clean_nlp << 1;
}