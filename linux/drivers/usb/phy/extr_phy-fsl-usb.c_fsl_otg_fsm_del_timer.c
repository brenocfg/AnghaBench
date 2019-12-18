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
struct otg_fsm {int dummy; } ;
struct fsl_otg_timer {int dummy; } ;
typedef  enum otg_fsm_timer { ____Placeholder_otg_fsm_timer } otg_fsm_timer ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_otg_del_timer (struct otg_fsm*,struct fsl_otg_timer*) ; 
 struct fsl_otg_timer* fsl_otg_get_timer (int) ; 

__attribute__((used)) static void fsl_otg_fsm_del_timer(struct otg_fsm *fsm, enum otg_fsm_timer t)
{
	struct fsl_otg_timer *timer;

	timer = fsl_otg_get_timer(t);
	if (!timer)
		return;

	fsl_otg_del_timer(fsm, timer);
}