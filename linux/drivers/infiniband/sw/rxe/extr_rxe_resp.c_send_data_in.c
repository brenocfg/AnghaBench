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
struct TYPE_4__ {TYPE_1__* wqe; } ;
struct rxe_qp {TYPE_2__ resp; int /*<<< orphan*/  pd; } ;
typedef  enum resp_states { ____Placeholder_resp_states } resp_states ;
struct TYPE_3__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 int RESPST_ERR_LENGTH ; 
 int RESPST_ERR_MALFORMED_WQE ; 
 int RESPST_NONE ; 
 int copy_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_mem_obj ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static enum resp_states send_data_in(struct rxe_qp *qp, void *data_addr,
				     int data_len)
{
	int err;

	err = copy_data(qp->pd, IB_ACCESS_LOCAL_WRITE, &qp->resp.wqe->dma,
			data_addr, data_len, to_mem_obj, NULL);
	if (unlikely(err))
		return (err == -ENOSPC) ? RESPST_ERR_LENGTH
					: RESPST_ERR_MALFORMED_WQE;

	return RESPST_NONE;
}