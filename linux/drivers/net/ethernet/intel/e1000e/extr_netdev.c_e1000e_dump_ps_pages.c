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
struct e1000_ps_page {scalar_t__ page; } ;
struct e1000_buffer {struct e1000_ps_page* ps_pages; } ;
struct e1000_adapter {int rx_ps_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_ADDRESS ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  page_address (scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e1000e_dump_ps_pages(struct e1000_adapter *adapter,
				 struct e1000_buffer *bi)
{
	int i;
	struct e1000_ps_page *ps_page;

	for (i = 0; i < adapter->rx_ps_pages; i++) {
		ps_page = &bi->ps_pages[i];

		if (ps_page->page) {
			pr_info("packet dump for ps_page %d:\n", i);
			print_hex_dump(KERN_INFO, "", DUMP_PREFIX_ADDRESS,
				       16, 1, page_address(ps_page->page),
				       PAGE_SIZE, true);
		}
	}
}