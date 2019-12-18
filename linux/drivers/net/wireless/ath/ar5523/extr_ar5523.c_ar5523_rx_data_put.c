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
struct ar5523_rx_data {int /*<<< orphan*/  list; } ;
struct ar5523 {int /*<<< orphan*/  rx_data_list_lock; int /*<<< orphan*/  rx_data_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ar5523_rx_data_put(struct ar5523 *ar,
				struct ar5523_rx_data *data)
{
	unsigned long flags;
	spin_lock_irqsave(&ar->rx_data_list_lock, flags);
	list_move(&data->list, &ar->rx_data_free);
	spin_unlock_irqrestore(&ar->rx_data_list_lock, flags);
}