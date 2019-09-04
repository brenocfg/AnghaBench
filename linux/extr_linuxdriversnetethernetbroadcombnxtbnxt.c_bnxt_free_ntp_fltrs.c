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
struct bnxt {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void bnxt_free_ntp_fltrs(struct bnxt *bp, bool irq_reinit)
{
#ifdef CONFIG_RFS_ACCEL
	int i;

	/* Under rtnl_lock and all our NAPIs have been disabled.  It's
	 * safe to delete the hash table.
	 */
	for (i = 0; i < BNXT_NTP_FLTR_HASH_SIZE; i++) {
		struct hlist_head *head;
		struct hlist_node *tmp;
		struct bnxt_ntuple_filter *fltr;

		head = &bp->ntp_fltr_hash_tbl[i];
		hlist_for_each_entry_safe(fltr, tmp, head, hash) {
			hlist_del(&fltr->hash);
			kfree(fltr);
		}
	}
	if (irq_reinit) {
		kfree(bp->ntp_fltr_bmap);
		bp->ntp_fltr_bmap = NULL;
	}
	bp->ntp_fltr_count = 0;
#endif
}