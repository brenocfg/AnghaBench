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
struct ar5523_rx_data {int /*<<< orphan*/  list; int /*<<< orphan*/  urb; } ;
struct TYPE_2__ {scalar_t__ next; } ;
struct ar5523 {int /*<<< orphan*/  rx_data_free_cnt; int /*<<< orphan*/  rx_data_free; int /*<<< orphan*/  rx_data_list_lock; TYPE_1__ rx_data_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar5523_cancel_rx_bufs(struct ar5523 *ar)
{
	struct ar5523_rx_data *data;
	unsigned long flags;

	do {
		spin_lock_irqsave(&ar->rx_data_list_lock, flags);
		if (!list_empty(&ar->rx_data_used))
			data = (struct ar5523_rx_data *) ar->rx_data_used.next;
		else
			data = NULL;
		spin_unlock_irqrestore(&ar->rx_data_list_lock, flags);

		if (!data)
			break;

		usb_kill_urb(data->urb);
		list_move(&data->list, &ar->rx_data_free);
		atomic_inc(&ar->rx_data_free_cnt);
	} while (data);
}