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
struct TYPE_2__ {scalar_t__ rdmap_op; } ;
struct siw_qp {TYPE_1__ rx_stream; int /*<<< orphan*/  rx_untagged; int /*<<< orphan*/ * rx_fpdu; int /*<<< orphan*/  rx_tagged; } ;

/* Variables and functions */
 scalar_t__ RDMAP_RDMA_READ_RESP ; 
 scalar_t__ RDMAP_RDMA_WRITE ; 

__attribute__((used)) static inline void set_rx_fpdu_context(struct siw_qp *qp, u8 opcode)
{
	if (opcode == RDMAP_RDMA_WRITE || opcode == RDMAP_RDMA_READ_RESP)
		qp->rx_fpdu = &qp->rx_tagged;
	else
		qp->rx_fpdu = &qp->rx_untagged;

	qp->rx_stream.rdmap_op = opcode;
}