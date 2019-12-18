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
typedef  int u32 ;
struct rvt_qpn_table {int incr; int nmaps; struct rvt_qpn_map* map; int /*<<< orphan*/  last; int /*<<< orphan*/  lock; } ;
struct rvt_qpn_map {int /*<<< orphan*/  page; } ;
struct TYPE_2__ {int qpn_res_end; int qpn_res_start; int qpn_inc; int qos_shift; int /*<<< orphan*/  qpn_start; } ;
struct rvt_dev_info {TYPE_1__ dparms; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int RVT_BITS_PER_PAGE ; 
 int RVT_BITS_PER_PAGE_MASK ; 
 int /*<<< orphan*/  get_map_page (struct rvt_qpn_table*,struct rvt_qpn_map*) ; 
 int /*<<< orphan*/  rvt_pr_info (struct rvt_dev_info*,char*,int,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_qpn_table(struct rvt_dev_info *rdi, struct rvt_qpn_table *qpt)
{
	u32 offset, i;
	struct rvt_qpn_map *map;
	int ret = 0;

	if (!(rdi->dparms.qpn_res_end >= rdi->dparms.qpn_res_start))
		return -EINVAL;

	spin_lock_init(&qpt->lock);

	qpt->last = rdi->dparms.qpn_start;
	qpt->incr = rdi->dparms.qpn_inc << rdi->dparms.qos_shift;

	/*
	 * Drivers may want some QPs beyond what we need for verbs let them use
	 * our qpn table. No need for two. Lets go ahead and mark the bitmaps
	 * for those. The reserved range must be *after* the range which verbs
	 * will pick from.
	 */

	/* Figure out number of bit maps needed before reserved range */
	qpt->nmaps = rdi->dparms.qpn_res_start / RVT_BITS_PER_PAGE;

	/* This should always be zero */
	offset = rdi->dparms.qpn_res_start & RVT_BITS_PER_PAGE_MASK;

	/* Starting with the first reserved bit map */
	map = &qpt->map[qpt->nmaps];

	rvt_pr_info(rdi, "Reserving QPNs from 0x%x to 0x%x for non-verbs use\n",
		    rdi->dparms.qpn_res_start, rdi->dparms.qpn_res_end);
	for (i = rdi->dparms.qpn_res_start; i <= rdi->dparms.qpn_res_end; i++) {
		if (!map->page) {
			get_map_page(qpt, map);
			if (!map->page) {
				ret = -ENOMEM;
				break;
			}
		}
		set_bit(offset, map->page);
		offset++;
		if (offset == RVT_BITS_PER_PAGE) {
			/* next page */
			qpt->nmaps++;
			map++;
			offset = 0;
		}
	}
	return ret;
}