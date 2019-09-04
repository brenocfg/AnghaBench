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
struct be_rx_page_info {int /*<<< orphan*/  page; } ;
struct be_queue_info {scalar_t__ head; scalar_t__ tail; int /*<<< orphan*/  used; } ;
struct be_rx_obj {struct be_queue_info q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct be_rx_page_info* get_rx_page_info (struct be_rx_obj*) ; 
 int /*<<< orphan*/  memset (struct be_rx_page_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_rxq_clean(struct be_rx_obj *rxo)
{
	struct be_queue_info *rxq = &rxo->q;
	struct be_rx_page_info *page_info;

	while (atomic_read(&rxq->used) > 0) {
		page_info = get_rx_page_info(rxo);
		put_page(page_info->page);
		memset(page_info, 0, sizeof(*page_info));
	}
	BUG_ON(atomic_read(&rxq->used));
	rxq->tail = 0;
	rxq->head = 0;
}