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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct ishtp_cl {int /*<<< orphan*/  tx_list_spinlock; TYPE_1__ tx_list; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool ishtp_cl_tx_empty(struct ishtp_cl *cl)
{
	int tx_list_empty;
	unsigned long tx_flags;

	spin_lock_irqsave(&cl->tx_list_spinlock, tx_flags);
	tx_list_empty = list_empty(&cl->tx_list.list);
	spin_unlock_irqrestore(&cl->tx_list_spinlock, tx_flags);

	return !!tx_list_empty;
}