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
struct rvt_qp {int s_flags; scalar_t__ s_hdrwords; } ;

/* Variables and functions */
 int RVT_S_ANY_WAIT_IO ; 
 int RVT_S_ANY_WAIT_SEND ; 
 int RVT_S_BUSY ; 
 int RVT_S_RESP_PENDING ; 

__attribute__((used)) static inline int qib_send_ok(struct rvt_qp *qp)
{
	return !(qp->s_flags & (RVT_S_BUSY | RVT_S_ANY_WAIT_IO)) &&
		(qp->s_hdrwords || (qp->s_flags & RVT_S_RESP_PENDING) ||
		 !(qp->s_flags & RVT_S_ANY_WAIT_SEND));
}