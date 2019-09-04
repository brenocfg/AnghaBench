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
struct filter_entry {scalar_t__ pending; scalar_t__ valid; } ;
struct TYPE_2__ {unsigned int nftids; unsigned int nsftids; struct filter_entry* ftid_tab; } ;
struct adapter {TYPE_1__ tids; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_filter (struct adapter*,struct filter_entry*) ; 

void clear_all_filters(struct adapter *adapter)
{
	unsigned int i;

	if (adapter->tids.ftid_tab) {
		struct filter_entry *f = &adapter->tids.ftid_tab[0];
		unsigned int max_ftid = adapter->tids.nftids +
					adapter->tids.nsftids;

		for (i = 0; i < max_ftid; i++, f++)
			if (f->valid || f->pending)
				clear_filter(adapter, f);
	}
}