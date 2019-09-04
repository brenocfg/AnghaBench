#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; } ;
struct TYPE_8__ {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; } ;
struct sec_queue {TYPE_1__ ring_cmd; TYPE_4__ ring_cq; TYPE_3__ ring_db; TYPE_2__* dev_info; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_Q_CMD_SIZE ; 
 int /*<<< orphan*/  SEC_Q_CQ_SIZE ; 
 int /*<<< orphan*/  SEC_Q_DB_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sec_queue_free_ring_pages(struct sec_queue *queue)
{
	struct device *dev = queue->dev_info->dev;

	dma_free_coherent(dev, SEC_Q_DB_SIZE, queue->ring_db.vaddr,
			  queue->ring_db.paddr);
	dma_free_coherent(dev, SEC_Q_CQ_SIZE, queue->ring_cq.vaddr,
			  queue->ring_cq.paddr);
	dma_free_coherent(dev, SEC_Q_CMD_SIZE, queue->ring_cmd.vaddr,
			  queue->ring_cmd.paddr);
}