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
struct pdc_state {int /*<<< orphan*/  last_tx_not_done; } ;
struct mbox_chan {struct pdc_state* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDC_RING_SPACE_MIN ; 
 int /*<<< orphan*/  pdc_rings_full (struct pdc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pdc_last_tx_done(struct mbox_chan *chan)
{
	struct pdc_state *pdcs = chan->con_priv;
	bool ret;

	if (unlikely(pdc_rings_full(pdcs, PDC_RING_SPACE_MIN,
				    PDC_RING_SPACE_MIN))) {
		pdcs->last_tx_not_done++;
		ret = false;
	} else {
		ret = true;
	}
	return ret;
}