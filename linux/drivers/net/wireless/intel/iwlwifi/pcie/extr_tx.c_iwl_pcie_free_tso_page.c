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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ cb; } ;
struct page {int dummy; } ;
struct iwl_trans_pcie {int page_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (struct page*) ; 

void iwl_pcie_free_tso_page(struct iwl_trans_pcie *trans_pcie,
			    struct sk_buff *skb)
{
	struct page **page_ptr;

	page_ptr = (void *)((u8 *)skb->cb + trans_pcie->page_offs);

	if (*page_ptr) {
		__free_page(*page_ptr);
		*page_ptr = NULL;
	}
}