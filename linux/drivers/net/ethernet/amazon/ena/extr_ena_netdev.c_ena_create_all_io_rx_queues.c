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
struct ena_com_dev {int dummy; } ;
struct ena_adapter {int num_queues; TYPE_2__* ena_napi; struct ena_com_dev* ena_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct TYPE_4__ {TYPE_1__ dim; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_IO_RXQ_IDX (int) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ena_com_destroy_io_queue (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int ena_create_io_rx_queue (struct ena_adapter*,int) ; 
 int /*<<< orphan*/  ena_dim_work ; 

__attribute__((used)) static int ena_create_all_io_rx_queues(struct ena_adapter *adapter)
{
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	int rc, i;

	for (i = 0; i < adapter->num_queues; i++) {
		rc = ena_create_io_rx_queue(adapter, i);
		if (rc)
			goto create_err;
		INIT_WORK(&adapter->ena_napi[i].dim.work, ena_dim_work);
	}

	return 0;

create_err:
	while (i--) {
		cancel_work_sync(&adapter->ena_napi[i].dim.work);
		ena_com_destroy_io_queue(ena_dev, ENA_IO_RXQ_IDX(i));
	}

	return rc;
}