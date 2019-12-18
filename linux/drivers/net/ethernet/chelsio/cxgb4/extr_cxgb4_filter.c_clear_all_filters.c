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
struct net_device {int dummy; } ;
struct filter_entry {int /*<<< orphan*/  fs; scalar_t__ pending; scalar_t__ valid; } ;
struct TYPE_2__ {unsigned int nftids; unsigned int nsftids; unsigned int hash_base; unsigned int ntids; scalar_t__* tid_tab; struct filter_entry* ftid_tab; } ;
struct adapter {TYPE_1__ tids; struct net_device** port; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE_DB_SRVR_START_INDEX_A ; 
 int /*<<< orphan*/  cxgb4_del_filter (struct net_device*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_hashfilter (struct adapter*) ; 
 unsigned int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

void clear_all_filters(struct adapter *adapter)
{
	struct net_device *dev = adapter->port[0];
	unsigned int i;

	if (adapter->tids.ftid_tab) {
		struct filter_entry *f = &adapter->tids.ftid_tab[0];
		unsigned int max_ftid = adapter->tids.nftids +
					adapter->tids.nsftids;
		/* Clear all TCAM filters */
		for (i = 0; i < max_ftid; i++, f++)
			if (f->valid || f->pending)
				cxgb4_del_filter(dev, i, &f->fs);
	}

	/* Clear all hash filters */
	if (is_hashfilter(adapter) && adapter->tids.tid_tab) {
		struct filter_entry *f;
		unsigned int sb;

		for (i = adapter->tids.hash_base;
		     i <= adapter->tids.ntids; i++) {
			f = (struct filter_entry *)
				adapter->tids.tid_tab[i];

			if (f && (f->valid || f->pending))
				cxgb4_del_filter(dev, i, &f->fs);
		}

		sb = t4_read_reg(adapter, LE_DB_SRVR_START_INDEX_A);
		for (i = 0; i < sb; i++) {
			f = (struct filter_entry *)adapter->tids.tid_tab[i];

			if (f && (f->valid || f->pending))
				cxgb4_del_filter(dev, i, &f->fs);
		}
	}
}