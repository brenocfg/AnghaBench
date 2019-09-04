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
typedef  int u64 ;
typedef  size_t u32 ;
struct rmid_read {int evtid; int val; scalar_t__ first; TYPE_1__* d; } ;
struct mbm_state {int prev_bw_msr; int prev_msr; int chunks; } ;
struct TYPE_2__ {struct mbm_state* mbm_local; struct mbm_state* mbm_total; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QOS_L3_MBM_LOCAL_EVENT_ID 130 
#define  QOS_L3_MBM_TOTAL_EVENT_ID 129 
#define  QOS_L3_OCCUP_EVENT_ID 128 
 int RMID_VAL_ERROR ; 
 int RMID_VAL_UNAVAIL ; 
 int __rmid_read (size_t,int) ; 
 int mbm_overflow_count (int,int) ; 
 int /*<<< orphan*/  memset (struct mbm_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __mon_event_count(u32 rmid, struct rmid_read *rr)
{
	struct mbm_state *m;
	u64 chunks, tval;

	tval = __rmid_read(rmid, rr->evtid);
	if (tval & (RMID_VAL_ERROR | RMID_VAL_UNAVAIL)) {
		rr->val = tval;
		return -EINVAL;
	}
	switch (rr->evtid) {
	case QOS_L3_OCCUP_EVENT_ID:
		rr->val += tval;
		return 0;
	case QOS_L3_MBM_TOTAL_EVENT_ID:
		m = &rr->d->mbm_total[rmid];
		break;
	case QOS_L3_MBM_LOCAL_EVENT_ID:
		m = &rr->d->mbm_local[rmid];
		break;
	default:
		/*
		 * Code would never reach here because
		 * an invalid event id would fail the __rmid_read.
		 */
		return -EINVAL;
	}

	if (rr->first) {
		memset(m, 0, sizeof(struct mbm_state));
		m->prev_bw_msr = m->prev_msr = tval;
		return 0;
	}

	chunks = mbm_overflow_count(m->prev_msr, tval);
	m->chunks += chunks;
	m->prev_msr = tval;

	rr->val += m->chunks;
	return 0;
}