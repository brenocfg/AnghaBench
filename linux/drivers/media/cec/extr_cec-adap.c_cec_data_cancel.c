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
typedef  int u8 ;
struct TYPE_4__ {int tx_status; int /*<<< orphan*/  tx_error_cnt; void* tx_ts; int /*<<< orphan*/  rx_status; void* rx_ts; } ;
struct cec_data {TYPE_2__ msg; TYPE_1__* adap; scalar_t__ attempts; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  transmit_queue_sz; struct cec_data* transmitting; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_RX_STATUS_ABORTED ; 
 int CEC_TX_STATUS_MAX_RETRIES ; 
 int CEC_TX_STATUS_OK ; 
 int /*<<< orphan*/  cec_data_completed (struct cec_data*) ; 
 int /*<<< orphan*/  cec_queue_msg_monitor (TYPE_1__*,TYPE_2__*,int) ; 
 void* ktime_get_ns () ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cec_data_cancel(struct cec_data *data, u8 tx_status)
{
	/*
	 * It's either the current transmit, or it is a pending
	 * transmit. Take the appropriate action to clear it.
	 */
	if (data->adap->transmitting == data) {
		data->adap->transmitting = NULL;
	} else {
		list_del_init(&data->list);
		if (!(data->msg.tx_status & CEC_TX_STATUS_OK))
			data->adap->transmit_queue_sz--;
	}

	if (data->msg.tx_status & CEC_TX_STATUS_OK) {
		data->msg.rx_ts = ktime_get_ns();
		data->msg.rx_status = CEC_RX_STATUS_ABORTED;
	} else {
		data->msg.tx_ts = ktime_get_ns();
		data->msg.tx_status |= tx_status |
				       CEC_TX_STATUS_MAX_RETRIES;
		data->msg.tx_error_cnt++;
		data->attempts = 0;
	}

	/* Queue transmitted message for monitoring purposes */
	cec_queue_msg_monitor(data->adap, &data->msg, 1);

	cec_data_completed(data);
}