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
typedef  int u32 ;
struct qtnf_shm_ipc {int /*<<< orphan*/  irq_work; int /*<<< orphan*/  workqueue; TYPE_3__* shm_region; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
struct TYPE_6__ {TYPE_2__ headroom; } ;

/* Variables and functions */
 int QTNF_SHM_IPC_NEW_DATA ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qtnf_shm_ipc_irq_inbound_handler(struct qtnf_shm_ipc *ipc)
{
	u32 flags;

	flags = readl(&ipc->shm_region->headroom.hdr.flags);

	if (flags & QTNF_SHM_IPC_NEW_DATA)
		queue_work(ipc->workqueue, &ipc->irq_work);
}