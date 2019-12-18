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
typedef  int /*<<< orphan*/  u32 ;
struct enetc_si {TYPE_1__* pdev; } ;
struct enetc_pf {struct enetc_si* si; struct enetc_mac_filter* mac_filter; } ;
struct enetc_mac_filter {int mac_addr_cnt; scalar_t__ mac_hash_table; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EMETC_MAC_ADDR_FILT_RES ; 
 int MADDR_TYPE ; 
 int UC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  enetc_clear_mac_flt_entry (struct enetc_si*,int) ; 
 int /*<<< orphan*/  enetc_clear_mac_ht_flt (struct enetc_si*,int /*<<< orphan*/ ,int) ; 
 int enetc_set_mac_flt_entry (struct enetc_si*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_set_mac_ht_flt (struct enetc_si*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enetc_sync_mac_filters(struct enetc_pf *pf)
{
	struct enetc_mac_filter *f = pf->mac_filter;
	struct enetc_si *si = pf->si;
	int i, pos;

	pos = EMETC_MAC_ADDR_FILT_RES;

	for (i = 0; i < MADDR_TYPE; i++, f++) {
		bool em = (f->mac_addr_cnt == 1) && (i == UC);
		bool clear = !f->mac_addr_cnt;

		if (clear) {
			if (i == UC)
				enetc_clear_mac_flt_entry(si, pos);

			enetc_clear_mac_ht_flt(si, 0, i);
			continue;
		}

		/* exact match filter */
		if (em) {
			int err;

			enetc_clear_mac_ht_flt(si, 0, UC);

			err = enetc_set_mac_flt_entry(si, pos, f->mac_addr,
						      BIT(0));
			if (!err)
				continue;

			/* fallback to HT filtering */
			dev_warn(&si->pdev->dev, "fallback to HT filt (%d)\n",
				 err);
		}

		/* hash table filter, clear EM filter for UC entries */
		if (i == UC)
			enetc_clear_mac_flt_entry(si, pos);

		enetc_set_mac_ht_flt(si, 0, i, (u32 *)f->mac_hash_table);
	}
}