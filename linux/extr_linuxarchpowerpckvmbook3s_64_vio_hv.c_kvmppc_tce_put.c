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
typedef  unsigned long u64 ;
struct page {int dummy; } ;
struct kvmppc_spapr_tce_table {struct page** pages; scalar_t__ offset; } ;

/* Variables and functions */
 unsigned long TCES_PER_PAGE ; 
 unsigned long* kvmppc_page_address (struct page*) ; 

void kvmppc_tce_put(struct kvmppc_spapr_tce_table *stt,
		unsigned long idx, unsigned long tce)
{
	struct page *page;
	u64 *tbl;

	idx -= stt->offset;
	page = stt->pages[idx / TCES_PER_PAGE];
	tbl = kvmppc_page_address(page);

	tbl[idx % TCES_PER_PAGE] = tce;
}