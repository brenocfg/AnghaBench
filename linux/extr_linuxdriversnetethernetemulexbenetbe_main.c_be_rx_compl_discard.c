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
typedef  scalar_t__ u16 ;
struct be_rx_page_info {int /*<<< orphan*/  page; } ;
struct be_rx_obj {int dummy; } ;
struct be_rx_compl_info {scalar_t__ num_rcvd; } ;

/* Variables and functions */
 struct be_rx_page_info* get_rx_page_info (struct be_rx_obj*) ; 
 int /*<<< orphan*/  memset (struct be_rx_page_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_rx_compl_discard(struct be_rx_obj *rxo,
				struct be_rx_compl_info *rxcp)
{
	struct be_rx_page_info *page_info;
	u16 i, num_rcvd = rxcp->num_rcvd;

	for (i = 0; i < num_rcvd; i++) {
		page_info = get_rx_page_info(rxo);
		put_page(page_info->page);
		memset(page_info, 0, sizeof(*page_info));
	}
}