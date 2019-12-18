#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct timer_list {int dummy; } ;
struct TYPE_4__ {scalar_t__ fill_cnt; scalar_t__ cnt; scalar_t__ watchdog_needed; } ;
struct myri10ge_slice_state {TYPE_2__ rx_big; TYPE_2__ rx_small; TYPE_1__* fw_stats; } ;
struct myri10ge_priv {int num_slices; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  watchdog_work; int /*<<< orphan*/  watchdog_pause; int /*<<< orphan*/  pdev; scalar_t__ big_bytes; scalar_t__ small_bytes; struct myri10ge_slice_state* ss; } ;
struct TYPE_3__ {int /*<<< orphan*/  dropped_pause; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ MXGEFW_PAD ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_MASTER ; 
 struct myri10ge_priv* from_timer (struct myri10ge_priv*,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  myri10ge_alloc_rx_pages (struct myri10ge_priv*,TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  myri10ge_check_slice (struct myri10ge_slice_state*,int*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ myri10ge_fill_thresh ; 
 int myri10ge_watchdog_timeout ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_timer ; 

__attribute__((used)) static void myri10ge_watchdog_timer(struct timer_list *t)
{
	struct myri10ge_priv *mgp;
	struct myri10ge_slice_state *ss;
	int i, reset_needed, busy_slice_cnt;
	u32 rx_pause_cnt;
	u16 cmd;

	mgp = from_timer(mgp, t, watchdog_timer);

	rx_pause_cnt = ntohl(mgp->ss[0].fw_stats->dropped_pause);
	busy_slice_cnt = 0;
	for (i = 0, reset_needed = 0;
	     i < mgp->num_slices && reset_needed == 0; ++i) {

		ss = &mgp->ss[i];
		if (ss->rx_small.watchdog_needed) {
			myri10ge_alloc_rx_pages(mgp, &ss->rx_small,
						mgp->small_bytes + MXGEFW_PAD,
						1);
			if (ss->rx_small.fill_cnt - ss->rx_small.cnt >=
			    myri10ge_fill_thresh)
				ss->rx_small.watchdog_needed = 0;
		}
		if (ss->rx_big.watchdog_needed) {
			myri10ge_alloc_rx_pages(mgp, &ss->rx_big,
						mgp->big_bytes, 1);
			if (ss->rx_big.fill_cnt - ss->rx_big.cnt >=
			    myri10ge_fill_thresh)
				ss->rx_big.watchdog_needed = 0;
		}
		myri10ge_check_slice(ss, &reset_needed, &busy_slice_cnt,
				     rx_pause_cnt);
	}
	/* if we've sent or received no traffic, poll the NIC to
	 * ensure it is still there.  Otherwise, we risk not noticing
	 * an error in a timely fashion */
	if (busy_slice_cnt == 0) {
		pci_read_config_word(mgp->pdev, PCI_COMMAND, &cmd);
		if ((cmd & PCI_COMMAND_MASTER) == 0) {
			reset_needed = 1;
		}
	}
	mgp->watchdog_pause = rx_pause_cnt;

	if (reset_needed) {
		schedule_work(&mgp->watchdog_work);
	} else {
		/* rearm timer */
		mod_timer(&mgp->watchdog_timer,
			  jiffies + myri10ge_watchdog_timeout * HZ);
	}
}