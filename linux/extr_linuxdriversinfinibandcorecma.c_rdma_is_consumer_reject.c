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
struct rdma_cm_id {int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int IB_CM_REJ_CONSUMER_DEFINED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ rdma_ib_or_roce (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_protocol_iwarp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool rdma_is_consumer_reject(struct rdma_cm_id *id, int reason)
{
	if (rdma_ib_or_roce(id->device, id->port_num))
		return reason == IB_CM_REJ_CONSUMER_DEFINED;

	if (rdma_protocol_iwarp(id->device, id->port_num))
		return reason == -ECONNREFUSED;

	WARN_ON_ONCE(1);
	return false;
}