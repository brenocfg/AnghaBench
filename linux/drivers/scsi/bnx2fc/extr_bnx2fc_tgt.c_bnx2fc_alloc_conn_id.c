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
typedef  size_t u32 ;
struct bnx2fc_rport {size_t fcoe_conn_id; } ;
struct bnx2fc_hba {size_t next_conn_id; int /*<<< orphan*/  hba_lock; struct bnx2fc_rport** tgt_ofld_list; } ;

/* Variables and functions */
 size_t BNX2FC_NUM_MAX_SESS ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 bnx2fc_alloc_conn_id(struct bnx2fc_hba *hba,
				struct bnx2fc_rport *tgt)
{
	u32 conn_id, next;

	/* called with hba mutex held */

	/*
	 * tgt_ofld_list access is synchronized using
	 * both hba mutex and hba lock. Atleast hba mutex or
	 * hba lock needs to be held for read access.
	 */

	spin_lock_bh(&hba->hba_lock);
	next = hba->next_conn_id;
	conn_id = hba->next_conn_id++;
	if (hba->next_conn_id == BNX2FC_NUM_MAX_SESS)
		hba->next_conn_id = 0;

	while (hba->tgt_ofld_list[conn_id] != NULL) {
		conn_id++;
		if (conn_id == BNX2FC_NUM_MAX_SESS)
			conn_id = 0;

		if (conn_id == next) {
			/* No free conn_ids are available */
			spin_unlock_bh(&hba->hba_lock);
			return -1;
		}
	}
	hba->tgt_ofld_list[conn_id] = tgt;
	tgt->fcoe_conn_id = conn_id;
	spin_unlock_bh(&hba->hba_lock);
	return conn_id;
}