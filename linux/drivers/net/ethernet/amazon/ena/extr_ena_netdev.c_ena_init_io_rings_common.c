#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct ena_ring {size_t qid; int first_interrupt; int /*<<< orphan*/  syncp; scalar_t__ no_interrupt_event_cnt; scalar_t__ cpu; scalar_t__ per_napi_packets; int /*<<< orphan*/  ena_dev; struct ena_adapter* adapter; int /*<<< orphan*/ * napi; int /*<<< orphan*/  netdev; int /*<<< orphan*/ * dev; TYPE_1__* pdev; } ;
struct ena_adapter {int /*<<< orphan*/  ena_dev; TYPE_2__* ena_napi; int /*<<< orphan*/  netdev; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  napi; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ena_init_io_rings_common(struct ena_adapter *adapter,
				     struct ena_ring *ring, u16 qid)
{
	ring->qid = qid;
	ring->pdev = adapter->pdev;
	ring->dev = &adapter->pdev->dev;
	ring->netdev = adapter->netdev;
	ring->napi = &adapter->ena_napi[qid].napi;
	ring->adapter = adapter;
	ring->ena_dev = adapter->ena_dev;
	ring->per_napi_packets = 0;
	ring->cpu = 0;
	ring->first_interrupt = false;
	ring->no_interrupt_event_cnt = 0;
	u64_stats_init(&ring->syncp);
}