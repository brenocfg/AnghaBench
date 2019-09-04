#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i40iw_sc_qp {scalar_t__ back_qp; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct i40iw_qp {TYPE_1__ terminate_timer; int /*<<< orphan*/  ibqp; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  i40iw_add_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_terminate_timeout ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i40iw_terminate_start_timer(struct i40iw_sc_qp *qp)
{
	struct i40iw_qp *iwqp;

	iwqp = (struct i40iw_qp *)qp->back_qp;
	i40iw_add_ref(&iwqp->ibqp);
	timer_setup(&iwqp->terminate_timer, i40iw_terminate_timeout, 0);
	iwqp->terminate_timer.expires = jiffies + HZ;
	add_timer(&iwqp->terminate_timer);
}