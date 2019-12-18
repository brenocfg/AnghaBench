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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct bfa_plog_s {scalar_t__ plog_enabled; } ;
struct TYPE_2__ {scalar_t__* int_log; } ;
struct bfa_plog_rec_s {int mid; int eid; scalar_t__ log_num_ints; TYPE_1__ log_entry; int /*<<< orphan*/  misc; int /*<<< orphan*/  log_type; } ;
typedef  enum bfa_plog_mid { ____Placeholder_bfa_plog_mid } bfa_plog_mid ;
typedef  enum bfa_plog_eid { ____Placeholder_bfa_plog_eid } bfa_plog_eid ;

/* Variables and functions */
 scalar_t__ BFA_PL_INT_LOG_SZ ; 
 int /*<<< orphan*/  BFA_PL_LOG_TYPE_INT ; 
 int /*<<< orphan*/  bfa_plog_add (struct bfa_plog_s*,struct bfa_plog_rec_s*) ; 
 int /*<<< orphan*/  memset (struct bfa_plog_rec_s*,int /*<<< orphan*/ ,int) ; 

void
bfa_plog_intarr(struct bfa_plog_s *plog, enum bfa_plog_mid mid,
		enum bfa_plog_eid event,
		u16 misc, u32 *intarr, u32 num_ints)
{
	struct bfa_plog_rec_s  lp;
	u32 i;

	if (num_ints > BFA_PL_INT_LOG_SZ)
		num_ints = BFA_PL_INT_LOG_SZ;

	if (plog->plog_enabled) {
		memset(&lp, 0, sizeof(struct bfa_plog_rec_s));
		lp.mid = mid;
		lp.eid = event;
		lp.log_type = BFA_PL_LOG_TYPE_INT;
		lp.misc = misc;

		for (i = 0; i < num_ints; i++)
			lp.log_entry.int_log[i] = intarr[i];

		lp.log_num_ints = (u8) num_ints;

		bfa_plog_add(plog, &lp);
	}
}