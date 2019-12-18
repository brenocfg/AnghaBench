#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct macstat {scalar_t__* txfunfl; scalar_t__ rxf0ovfl; } ;
struct brcms_c_info {TYPE_3__* hw; TYPE_2__* pub; TYPE_1__* core; } ;
struct TYPE_6__ {scalar_t__* di; int /*<<< orphan*/  d11core; } ;
struct TYPE_5__ {int /*<<< orphan*/  unit; int /*<<< orphan*/  up; } ;
struct TYPE_4__ {struct macstat* macstat_snapshot; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_UCODE_MACSTAT ; 
 int NFIFO ; 
 int /*<<< orphan*/  OBJADDR_SHM_SEL ; 
 int /*<<< orphan*/  brcms_b_copyfrom_objmem (TYPE_3__*,int /*<<< orphan*/ ,struct macstat*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  dma_counterreset (scalar_t__) ; 

__attribute__((used)) static void brcms_c_statsupd(struct brcms_c_info *wlc)
{
	int i;
	struct macstat *macstats;
#ifdef DEBUG
	u16 delta;
	u16 rxf0ovfl;
	u16 txfunfl[NFIFO];
#endif				/* DEBUG */

	/* if driver down, make no sense to update stats */
	if (!wlc->pub->up)
		return;

	macstats = wlc->core->macstat_snapshot;

#ifdef DEBUG
	/* save last rx fifo 0 overflow count */
	rxf0ovfl = macstats->rxf0ovfl;

	/* save last tx fifo  underflow count */
	for (i = 0; i < NFIFO; i++)
		txfunfl[i] = macstats->txfunfl[i];
#endif				/* DEBUG */

	/* Read mac stats from contiguous shared memory */
	brcms_b_copyfrom_objmem(wlc->hw, M_UCODE_MACSTAT, macstats,
				sizeof(*macstats), OBJADDR_SHM_SEL);

#ifdef DEBUG
	/* check for rx fifo 0 overflow */
	delta = (u16)(macstats->rxf0ovfl - rxf0ovfl);
	if (delta)
		brcms_err(wlc->hw->d11core, "wl%d: %u rx fifo 0 overflows!\n",
			  wlc->pub->unit, delta);

	/* check for tx fifo underflows */
	for (i = 0; i < NFIFO; i++) {
		delta = macstats->txfunfl[i] - txfunfl[i];
		if (delta)
			brcms_err(wlc->hw->d11core,
				  "wl%d: %u tx fifo %d underflows!\n",
				  wlc->pub->unit, delta, i);
	}
#endif				/* DEBUG */

	/* merge counters from dma module */
	for (i = 0; i < NFIFO; i++) {
		if (wlc->hw->di[i])
			dma_counterreset(wlc->hw->di[i]);
	}
}