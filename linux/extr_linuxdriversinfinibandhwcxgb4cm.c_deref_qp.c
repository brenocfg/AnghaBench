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
struct TYPE_4__ {int /*<<< orphan*/  history; int /*<<< orphan*/  flags; TYPE_1__* qp; } ;
struct c4iw_ep {TYPE_2__ com; } ;
struct TYPE_3__ {int /*<<< orphan*/  ibqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  QP_DEREFED ; 
 int /*<<< orphan*/  QP_REFERENCED ; 
 int /*<<< orphan*/  c4iw_qp_rem_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deref_qp(struct c4iw_ep *ep)
{
	c4iw_qp_rem_ref(&ep->com.qp->ibqp);
	clear_bit(QP_REFERENCED, &ep->com.flags);
	set_bit(QP_DEREFED, &ep->com.history);
}