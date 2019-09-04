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
struct ldc_channel {unsigned long rx_head; unsigned long rx_tail; unsigned long chan_state; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int EAGAIN ; 
 int ECONNRESET ; 
 int LDC_ABORT (struct ldc_channel*) ; 
 unsigned long LDC_CHANNEL_DOWN ; 
 unsigned long LDC_CHANNEL_RESETTING ; 
 int /*<<< orphan*/  ldcdbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,unsigned long) ; 
 unsigned long sun4v_ldc_rx_get_state (int /*<<< orphan*/ ,unsigned long*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rx_data_wait(struct ldc_channel *lp, unsigned long cur_head)
{
	unsigned long dummy;
	int limit = 1000;

	ldcdbg(DATA, "DATA WAIT cur_head[%lx] rx_head[%lx] rx_tail[%lx]\n",
	       cur_head, lp->rx_head, lp->rx_tail);
	while (limit-- > 0) {
		unsigned long hv_err;

		hv_err = sun4v_ldc_rx_get_state(lp->id,
						&dummy,
						&lp->rx_tail,
						&lp->chan_state);
		if (hv_err)
			return LDC_ABORT(lp);

		if (lp->chan_state == LDC_CHANNEL_DOWN ||
		    lp->chan_state == LDC_CHANNEL_RESETTING)
			return -ECONNRESET;

		if (cur_head != lp->rx_tail) {
			ldcdbg(DATA, "DATA WAIT DONE "
			       "head[%lx] tail[%lx] chan_state[%lx]\n",
			       dummy, lp->rx_tail, lp->chan_state);
			return 0;
		}

		udelay(1);
	}
	return -EAGAIN;
}