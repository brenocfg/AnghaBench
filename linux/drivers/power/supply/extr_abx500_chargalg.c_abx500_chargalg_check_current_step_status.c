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
struct TYPE_2__ {int curr_step_change; } ;
struct abx500_chargalg {TYPE_1__ curr_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_NORMAL_INIT ; 
 int /*<<< orphan*/  abx500_chargalg_state_to (struct abx500_chargalg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void abx500_chargalg_check_current_step_status
	(struct abx500_chargalg *di)
{
	if (di->curr_status.curr_step_change)
		abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
	di->curr_status.curr_step_change = false;
}