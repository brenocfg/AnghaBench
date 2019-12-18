#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct zfcp_qdio_req {int /*<<< orphan*/  sbal_first; scalar_t__ sbal_number; } ;
struct zfcp_qdio {int /*<<< orphan*/  req_q_idx; int /*<<< orphan*/  req_q_free; int /*<<< orphan*/  req_q; TYPE_1__* adapter; int /*<<< orphan*/  stat_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  ccw_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  QDIO_FLAG_SYNC_OUTPUT ; 
 int /*<<< orphan*/  QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  atomic_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 int do_QDIO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zfcp_qdio_account (struct zfcp_qdio*) ; 
 int /*<<< orphan*/  zfcp_qdio_zero_sbals (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int zfcp_qdio_send(struct zfcp_qdio *qdio, struct zfcp_qdio_req *q_req)
{
	int retval;
	u8 sbal_number = q_req->sbal_number;

	spin_lock(&qdio->stat_lock);
	zfcp_qdio_account(qdio);
	spin_unlock(&qdio->stat_lock);

	retval = do_QDIO(qdio->adapter->ccw_device, QDIO_FLAG_SYNC_OUTPUT, 0,
			 q_req->sbal_first, sbal_number);

	if (unlikely(retval)) {
		zfcp_qdio_zero_sbals(qdio->req_q, q_req->sbal_first,
				     sbal_number);
		return retval;
	}

	/* account for transferred buffers */
	atomic_sub(sbal_number, &qdio->req_q_free);
	qdio->req_q_idx += sbal_number;
	qdio->req_q_idx %= QDIO_MAX_BUFFERS_PER_Q;

	return 0;
}