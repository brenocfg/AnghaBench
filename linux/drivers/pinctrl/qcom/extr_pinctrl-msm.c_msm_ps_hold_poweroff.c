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
struct TYPE_2__ {int /*<<< orphan*/  restart_nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_ps_hold_restart (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* poweroff_pctrl ; 

__attribute__((used)) static void msm_ps_hold_poweroff(void)
{
	msm_ps_hold_restart(&poweroff_pctrl->restart_nb, 0, NULL);
}