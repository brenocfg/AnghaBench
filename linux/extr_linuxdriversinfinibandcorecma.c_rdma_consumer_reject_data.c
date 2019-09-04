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
typedef  scalar_t__ u8 ;
struct rdma_cm_id {int dummy; } ;
struct TYPE_3__ {void* private_data; scalar_t__ private_data_len; } ;
struct TYPE_4__ {TYPE_1__ conn; } ;
struct rdma_cm_event {TYPE_2__ param; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 scalar_t__ rdma_is_consumer_reject (struct rdma_cm_id*,int /*<<< orphan*/ ) ; 

const void *rdma_consumer_reject_data(struct rdma_cm_id *id,
				      struct rdma_cm_event *ev, u8 *data_len)
{
	const void *p;

	if (rdma_is_consumer_reject(id, ev->status)) {
		*data_len = ev->param.conn.private_data_len;
		p = ev->param.conn.private_data;
	} else {
		*data_len = 0;
		p = NULL;
	}
	return p;
}