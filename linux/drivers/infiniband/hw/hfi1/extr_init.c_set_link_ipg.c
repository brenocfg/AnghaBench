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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct hfi1_pportdata {int /*<<< orphan*/  ibmaxlen; TYPE_1__* cca_timer; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int dummy; } ;
struct TYPE_6__ {scalar_t__ ccti_limit; TYPE_2__* entries; } ;
struct cc_state {TYPE_3__ cct; } ;
struct TYPE_5__ {scalar_t__ entry; } ;
struct TYPE_4__ {scalar_t__ ccti; } ;

/* Variables and functions */
 int OPA_MAX_SLS ; 
 int /*<<< orphan*/  SEND_STATIC_RATE_CONTROL ; 
 scalar_t__ SEND_STATIC_RATE_CONTROL_CSR_SRC_RELOAD_SHIFT ; 
 scalar_t__ SEND_STATIC_RATE_CONTROL_CSR_SRC_RELOAD_SMASK ; 
 scalar_t__ active_egress_rate (struct hfi1_pportdata*) ; 
 scalar_t__ egress_cycles (int /*<<< orphan*/ ,scalar_t__) ; 
 struct cc_state* get_cc_state (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,scalar_t__) ; 

void set_link_ipg(struct hfi1_pportdata *ppd)
{
	struct hfi1_devdata *dd = ppd->dd;
	struct cc_state *cc_state;
	int i;
	u16 cce, ccti_limit, max_ccti = 0;
	u16 shift, mult;
	u64 src;
	u32 current_egress_rate; /* Mbits /sec */
	u32 max_pkt_time;
	/*
	 * max_pkt_time is the maximum packet egress time in units
	 * of the fabric clock period 1/(805 MHz).
	 */

	cc_state = get_cc_state(ppd);

	if (!cc_state)
		/*
		 * This should _never_ happen - rcu_read_lock() is held,
		 * and set_link_ipg() should not be called if cc_state
		 * is NULL.
		 */
		return;

	for (i = 0; i < OPA_MAX_SLS; i++) {
		u16 ccti = ppd->cca_timer[i].ccti;

		if (ccti > max_ccti)
			max_ccti = ccti;
	}

	ccti_limit = cc_state->cct.ccti_limit;
	if (max_ccti > ccti_limit)
		max_ccti = ccti_limit;

	cce = cc_state->cct.entries[max_ccti].entry;
	shift = (cce & 0xc000) >> 14;
	mult = (cce & 0x3fff);

	current_egress_rate = active_egress_rate(ppd);

	max_pkt_time = egress_cycles(ppd->ibmaxlen, current_egress_rate);

	src = (max_pkt_time >> shift) * mult;

	src &= SEND_STATIC_RATE_CONTROL_CSR_SRC_RELOAD_SMASK;
	src <<= SEND_STATIC_RATE_CONTROL_CSR_SRC_RELOAD_SHIFT;

	write_csr(dd, SEND_STATIC_RATE_CONTROL, src);
}