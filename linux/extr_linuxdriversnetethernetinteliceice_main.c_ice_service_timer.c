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
struct ice_pf {scalar_t__ serv_tmr_period; int /*<<< orphan*/  serv_tmr; } ;

/* Variables and functions */
 struct ice_pf* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_service_task_schedule (struct ice_pf*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ice_pf* pf ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  serv_tmr ; 

__attribute__((used)) static void ice_service_timer(struct timer_list *t)
{
	struct ice_pf *pf = from_timer(pf, t, serv_tmr);

	mod_timer(&pf->serv_tmr, round_jiffies(pf->serv_tmr_period + jiffies));
	ice_service_task_schedule(pf);
}