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
struct ena_com_dev {int dummy; } ;
struct ena_adapter {int num_queues; struct ena_com_dev* ena_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_IO_TXQ_IDX (int) ; 
 int /*<<< orphan*/  ena_com_destroy_io_queue (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int ena_create_io_tx_queue (struct ena_adapter*,int) ; 

__attribute__((used)) static int ena_create_all_io_tx_queues(struct ena_adapter *adapter)
{
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	int rc, i;

	for (i = 0; i < adapter->num_queues; i++) {
		rc = ena_create_io_tx_queue(adapter, i);
		if (rc)
			goto create_err;
	}

	return 0;

create_err:
	while (i--)
		ena_com_destroy_io_queue(ena_dev, ENA_IO_TXQ_IDX(i));

	return rc;
}