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
struct rx_cxt {int /*<<< orphan*/  free_list_lock; int /*<<< orphan*/  rx_free_list; } ;
struct mux_rx {int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void put_rx_struct(struct rx_cxt *rx, struct mux_rx *r)
{
	unsigned long flags;

	spin_lock_irqsave(&rx->free_list_lock, flags);
	list_add_tail(&r->free_list, &rx->rx_free_list);
	spin_unlock_irqrestore(&rx->free_list_lock, flags);
}