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
typedef  int /*<<< orphan*/  u16 ;
struct ena_adapter {int num_queues; int /*<<< orphan*/  ena_dev; TYPE_2__* ena_napi; } ;
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct TYPE_4__ {TYPE_1__ dim; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_IO_RXQ_IDX (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ena_com_destroy_io_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_destroy_all_rx_queues(struct ena_adapter *adapter)
{
	u16 ena_qid;
	int i;

	for (i = 0; i < adapter->num_queues; i++) {
		ena_qid = ENA_IO_RXQ_IDX(i);
		cancel_work_sync(&adapter->ena_napi[i].dim.work);
		ena_com_destroy_io_queue(adapter->ena_dev, ena_qid);
	}
}