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
typedef  int u16 ;
struct ptp_clock_event {int timestamp; int index; int /*<<< orphan*/  type; } ;
struct phy_txts {int /*<<< orphan*/  ns_lo; int /*<<< orphan*/  ns_hi; int /*<<< orphan*/  sec_lo; int /*<<< orphan*/  sec_hi; } ;
struct TYPE_4__ {int /*<<< orphan*/  ns_lo; int /*<<< orphan*/  ns_hi; int /*<<< orphan*/  sec_lo; int /*<<< orphan*/  sec_hi; } ;
struct dp83640_private {TYPE_1__* clock; TYPE_2__ edata; } ;
typedef  int /*<<< orphan*/  ext_status ;
struct TYPE_3__ {int /*<<< orphan*/  ptp_clock; } ;

/* Variables and functions */
 int EVNT_NUM_MASK ; 
 int EVNT_NUM_SHIFT ; 
 int EVNT_TS_LEN_MASK ; 
 int EVNT_TS_LEN_SHIFT ; 
 int EXT_EVENT ; 
 int MULT_EVNT ; 
 int N_EXT_TS ; 
 int /*<<< orphan*/  PTP_CLOCK_EXTTS ; 
 int exts_chan_to_edata (int) ; 
 int phy2txts (TYPE_2__*) ; 
 int /*<<< orphan*/  ptp_clock_event (int /*<<< orphan*/ ,struct ptp_clock_event*) ; 

__attribute__((used)) static int decode_evnt(struct dp83640_private *dp83640,
		       void *data, int len, u16 ests)
{
	struct phy_txts *phy_txts;
	struct ptp_clock_event event;
	int i, parsed;
	int words = (ests >> EVNT_TS_LEN_SHIFT) & EVNT_TS_LEN_MASK;
	u16 ext_status = 0;

	/* calculate length of the event timestamp status message */
	if (ests & MULT_EVNT)
		parsed = (words + 2) * sizeof(u16);
	else
		parsed = (words + 1) * sizeof(u16);

	/* check if enough data is available */
	if (len < parsed)
		return len;

	if (ests & MULT_EVNT) {
		ext_status = *(u16 *) data;
		data += sizeof(ext_status);
	}

	phy_txts = data;

	switch (words) {
	case 3:
		dp83640->edata.sec_hi = phy_txts->sec_hi;
		/* fall through */
	case 2:
		dp83640->edata.sec_lo = phy_txts->sec_lo;
		/* fall through */
	case 1:
		dp83640->edata.ns_hi = phy_txts->ns_hi;
		/* fall through */
	case 0:
		dp83640->edata.ns_lo = phy_txts->ns_lo;
	}

	if (!ext_status) {
		i = ((ests >> EVNT_NUM_SHIFT) & EVNT_NUM_MASK) - EXT_EVENT;
		ext_status = exts_chan_to_edata(i);
	}

	event.type = PTP_CLOCK_EXTTS;
	event.timestamp = phy2txts(&dp83640->edata);

	/* Compensate for input path and synchronization delays */
	event.timestamp -= 35;

	for (i = 0; i < N_EXT_TS; i++) {
		if (ext_status & exts_chan_to_edata(i)) {
			event.index = i;
			ptp_clock_event(dp83640->clock->ptp_clock, &event);
		}
	}

	return parsed;
}