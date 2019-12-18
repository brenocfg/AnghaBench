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
struct oslec_state {int taps; int curr_pos; int cng_level; int lbgn_upper; int lbgn_upper_acc; struct oslec_state** fir_taps16; int /*<<< orphan*/  fir_state; int /*<<< orphan*/  fir_state_bg; scalar_t__ lbgn_acc; scalar_t__ lbgn; scalar_t__ rx_2; scalar_t__ rx_1; scalar_t__ tx_2; scalar_t__ tx_1; scalar_t__ lclean_bg; scalar_t__ lclean; scalar_t__ lrx; scalar_t__ ltx; scalar_t__ lclean_bgacc; scalar_t__ lcleanacc; scalar_t__ lrxacc; scalar_t__ ltxacc; scalar_t__ pstates; scalar_t__ cond_met; void* snapshot; scalar_t__* yvrx; scalar_t__* xvrx; scalar_t__* yvtx; scalar_t__* xvtx; int /*<<< orphan*/  log2taps; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * fir16_create (int /*<<< orphan*/ *,struct oslec_state*,int) ; 
 int /*<<< orphan*/  fir16_free (int /*<<< orphan*/ *) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct oslec_state*) ; 
 struct oslec_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oslec_adaption_mode (struct oslec_state*,int) ; 
 int /*<<< orphan*/  top_bit (int) ; 

struct oslec_state *oslec_create(int len, int adaption_mode)
{
	struct oslec_state *ec;
	int i;
	const int16_t *history;

	ec = kzalloc(sizeof(*ec), GFP_KERNEL);
	if (!ec)
		return NULL;

	ec->taps = len;
	ec->log2taps = top_bit(len);
	ec->curr_pos = ec->taps - 1;

	ec->fir_taps16[0] =
	    kcalloc(ec->taps, sizeof(int16_t), GFP_KERNEL);
	if (!ec->fir_taps16[0])
		goto error_oom_0;

	ec->fir_taps16[1] =
	    kcalloc(ec->taps, sizeof(int16_t), GFP_KERNEL);
	if (!ec->fir_taps16[1])
		goto error_oom_1;

	history = fir16_create(&ec->fir_state, ec->fir_taps16[0], ec->taps);
	if (!history)
		goto error_state;
	history = fir16_create(&ec->fir_state_bg, ec->fir_taps16[1], ec->taps);
	if (!history)
		goto error_state_bg;

	for (i = 0; i < 5; i++)
		ec->xvtx[i] = ec->yvtx[i] = ec->xvrx[i] = ec->yvrx[i] = 0;

	ec->cng_level = 1000;
	oslec_adaption_mode(ec, adaption_mode);

	ec->snapshot = kcalloc(ec->taps, sizeof(int16_t), GFP_KERNEL);
	if (!ec->snapshot)
		goto error_snap;

	ec->cond_met = 0;
	ec->pstates = 0;
	ec->ltxacc = ec->lrxacc = ec->lcleanacc = ec->lclean_bgacc = 0;
	ec->ltx = ec->lrx = ec->lclean = ec->lclean_bg = 0;
	ec->tx_1 = ec->tx_2 = ec->rx_1 = ec->rx_2 = 0;
	ec->lbgn = ec->lbgn_acc = 0;
	ec->lbgn_upper = 200;
	ec->lbgn_upper_acc = ec->lbgn_upper << 13;

	return ec;

error_snap:
	fir16_free(&ec->fir_state_bg);
error_state_bg:
	fir16_free(&ec->fir_state);
error_state:
	kfree(ec->fir_taps16[1]);
error_oom_1:
	kfree(ec->fir_taps16[0]);
error_oom_0:
	kfree(ec);
	return NULL;
}