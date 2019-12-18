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
struct ar5523_rx_data {int /*<<< orphan*/  urb; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {scalar_t__ next; } ;
struct ar5523 {TYPE_1__ rx_data_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar5523_cancel_rx_bufs (struct ar5523*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar5523_free_rx_bufs(struct ar5523 *ar)
{
	struct ar5523_rx_data *data;

	ar5523_cancel_rx_bufs(ar);
	while (!list_empty(&ar->rx_data_free)) {
		data = (struct ar5523_rx_data *) ar->rx_data_free.next;
		list_del(&data->list);
		usb_free_urb(data->urb);
	}
}