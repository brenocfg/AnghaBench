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
struct rxe_sq {int max_sge; unsigned int max_inline; } ;
struct rxe_qp {struct rxe_sq sq; } ;
struct ib_send_wr {int num_sge; int send_flags; } ;
struct TYPE_2__ {int remote_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_SEND_INLINE ; 
 unsigned int WR_ATOMIC_MASK ; 
 TYPE_1__* atomic_wr (struct ib_send_wr const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int validate_send_wr(struct rxe_qp *qp, const struct ib_send_wr *ibwr,
			    unsigned int mask, unsigned int length)
{
	int num_sge = ibwr->num_sge;
	struct rxe_sq *sq = &qp->sq;

	if (unlikely(num_sge > sq->max_sge))
		goto err1;

	if (unlikely(mask & WR_ATOMIC_MASK)) {
		if (length < 8)
			goto err1;

		if (atomic_wr(ibwr)->remote_addr & 0x7)
			goto err1;
	}

	if (unlikely((ibwr->send_flags & IB_SEND_INLINE) &&
		     (length > sq->max_inline)))
		goto err1;

	return 0;

err1:
	return -EINVAL;
}