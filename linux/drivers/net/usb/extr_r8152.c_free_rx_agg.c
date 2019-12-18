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
struct rx_agg {int /*<<< orphan*/  page; int /*<<< orphan*/  urb; int /*<<< orphan*/  info_list; } ;
struct r8152 {int /*<<< orphan*/  rx_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rx_agg*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_rx_agg(struct r8152 *tp, struct rx_agg *agg)
{
	list_del(&agg->info_list);

	usb_free_urb(agg->urb);
	put_page(agg->page);
	kfree(agg);

	atomic_dec(&tp->rx_count);
}