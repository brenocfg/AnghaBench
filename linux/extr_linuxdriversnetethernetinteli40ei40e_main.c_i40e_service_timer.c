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
struct i40e_pf {scalar_t__ service_timer_period; int /*<<< orphan*/  service_timer; } ;

/* Variables and functions */
 struct i40e_pf* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_service_event_schedule (struct i40e_pf*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct i40e_pf* pf ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  service_timer ; 

__attribute__((used)) static void i40e_service_timer(struct timer_list *t)
{
	struct i40e_pf *pf = from_timer(pf, t, service_timer);

	mod_timer(&pf->service_timer,
		  round_jiffies(jiffies + pf->service_timer_period));
	i40e_service_event_schedule(pf);
}