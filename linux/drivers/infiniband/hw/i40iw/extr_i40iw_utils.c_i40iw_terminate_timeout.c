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
struct timer_list {int dummy; } ;
struct i40iw_sc_qp {int dummy; } ;
struct i40iw_qp {int /*<<< orphan*/  ibqp; int /*<<< orphan*/  sc_qp; } ;

/* Variables and functions */
 struct i40iw_qp* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_rem_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_terminate_done (struct i40iw_sc_qp*,int) ; 
 struct i40iw_qp* iwqp ; 
 int /*<<< orphan*/  terminate_timer ; 

__attribute__((used)) static void i40iw_terminate_timeout(struct timer_list *t)
{
	struct i40iw_qp *iwqp = from_timer(iwqp, t, terminate_timer);
	struct i40iw_sc_qp *qp = (struct i40iw_sc_qp *)&iwqp->sc_qp;

	i40iw_terminate_done(qp, 1);
	i40iw_rem_ref(&iwqp->ibqp);
}