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
struct TYPE_2__ {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct pvrdma_qp {TYPE_1__ ibqp; } ;
struct pvrdma_cq {int dummy; } ;

/* Variables and functions */
 struct pvrdma_cq* to_vcq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void get_cqs(struct pvrdma_qp *qp, struct pvrdma_cq **send_cq,
			   struct pvrdma_cq **recv_cq)
{
	*send_cq = to_vcq(qp->ibqp.send_cq);
	*recv_cq = to_vcq(qp->ibqp.recv_cq);
}