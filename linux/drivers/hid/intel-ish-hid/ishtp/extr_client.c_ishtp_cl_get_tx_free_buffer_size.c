#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ishtp_cl {int tx_ring_free_size; int /*<<< orphan*/  tx_free_list_spinlock; TYPE_3__* device; } ;
struct TYPE_6__ {TYPE_2__* fw_client; } ;
struct TYPE_4__ {int max_msg_length; } ;
struct TYPE_5__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ishtp_cl_get_tx_free_buffer_size(struct ishtp_cl *cl)
{
	unsigned long tx_free_flags;
	int size;

	spin_lock_irqsave(&cl->tx_free_list_spinlock, tx_free_flags);
	size = cl->tx_ring_free_size * cl->device->fw_client->props.max_msg_length;
	spin_unlock_irqrestore(&cl->tx_free_list_spinlock, tx_free_flags);

	return size;
}