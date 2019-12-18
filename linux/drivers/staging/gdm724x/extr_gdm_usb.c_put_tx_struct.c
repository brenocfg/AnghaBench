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
struct usb_tx_sdu {int /*<<< orphan*/  list; } ;
struct tx_cxt {int /*<<< orphan*/  avail_count; int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_tx_struct(struct tx_cxt *tx, struct usb_tx_sdu *t_sdu)
{
	list_add_tail(&t_sdu->list, &tx->free_list);
	tx->avail_count++;
}