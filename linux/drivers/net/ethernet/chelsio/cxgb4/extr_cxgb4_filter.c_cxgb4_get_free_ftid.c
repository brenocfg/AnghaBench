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
struct tid_info {int nftids; int /*<<< orphan*/  ftid_lock; int /*<<< orphan*/  ftid_bmap; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; struct tid_info tids; } ;

/* Variables and functions */
 int PF_INET ; 
 int bitmap_find_free_region (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,int,int) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_t6 (int /*<<< orphan*/ ) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int cxgb4_get_free_ftid(struct net_device *dev, int family)
{
	struct adapter *adap = netdev2adap(dev);
	struct tid_info *t = &adap->tids;
	int ftid;

	spin_lock_bh(&t->ftid_lock);
	if (family == PF_INET) {
		ftid = find_first_zero_bit(t->ftid_bmap, t->nftids);
		if (ftid >= t->nftids)
			ftid = -1;
	} else {
		if (is_t6(adap->params.chip)) {
			ftid = bitmap_find_free_region(t->ftid_bmap,
						       t->nftids, 1);
			if (ftid < 0)
				goto out_unlock;

			/* this is only a lookup, keep the found region
			 * unallocated
			 */
			bitmap_release_region(t->ftid_bmap, ftid, 1);
		} else {
			ftid = bitmap_find_free_region(t->ftid_bmap,
						       t->nftids, 2);
			if (ftid < 0)
				goto out_unlock;

			bitmap_release_region(t->ftid_bmap, ftid, 2);
		}
	}
out_unlock:
	spin_unlock_bh(&t->ftid_lock);
	return ftid;
}