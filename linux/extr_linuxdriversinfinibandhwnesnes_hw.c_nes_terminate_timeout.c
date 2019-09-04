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
struct nes_qp {int dummy; } ;

/* Variables and functions */
 struct nes_qp* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_terminate_done (struct nes_qp*,int) ; 
 struct nes_qp* nesqp ; 
 int /*<<< orphan*/  terminate_timer ; 

void nes_terminate_timeout(struct timer_list *t)
{
	struct nes_qp *nesqp = from_timer(nesqp, t, terminate_timer);

	nes_terminate_done(nesqp, 1);
}