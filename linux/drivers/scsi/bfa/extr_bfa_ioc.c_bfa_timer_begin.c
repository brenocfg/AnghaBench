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
struct bfa_timer_s {unsigned int timeout; void (* timercb ) (void*) ;int /*<<< orphan*/  qe; void* arg; } ;
struct bfa_timer_mod_s {int /*<<< orphan*/  timer_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_q_is_on_q (int /*<<< orphan*/ *,struct bfa_timer_s*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bfa_timer_begin(struct bfa_timer_mod_s *mod, struct bfa_timer_s *timer,
		    void (*timercb) (void *), void *arg, unsigned int timeout)
{

	WARN_ON(timercb == NULL);
	WARN_ON(bfa_q_is_on_q(&mod->timer_q, timer));

	timer->timeout = timeout;
	timer->timercb = timercb;
	timer->arg = arg;

	list_add_tail(&timer->qe, &mod->timer_q);
}