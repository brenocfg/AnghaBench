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
struct cyapa_pip_cmd_states {int /*<<< orphan*/ * resp_len; int /*<<< orphan*/ * resp_data; int /*<<< orphan*/  in_progress_cmd; int /*<<< orphan*/ * resp_sort_func; int /*<<< orphan*/  pm_stage; int /*<<< orphan*/  pm_stage_lock; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  cmd_issued; int /*<<< orphan*/  cmd_ready; } ;
struct TYPE_2__ {struct cyapa_pip_cmd_states pip; } ;
struct cyapa {int /*<<< orphan*/  dev_sleep_time; int /*<<< orphan*/  dev_pwr_mode; TYPE_1__ cmd_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYAPA_PM_DEACTIVE ; 
 int /*<<< orphan*/  PIP_INVALID_CMD ; 
 int /*<<< orphan*/  UNINIT_PWR_MODE ; 
 int /*<<< orphan*/  UNINIT_SLEEP_TIME ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int cyapa_pip_cmd_state_initialize(struct cyapa *cyapa)
{
	struct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;

	init_completion(&pip->cmd_ready);
	atomic_set(&pip->cmd_issued, 0);
	mutex_init(&pip->cmd_lock);

	mutex_init(&pip->pm_stage_lock);
	pip->pm_stage = CYAPA_PM_DEACTIVE;

	pip->resp_sort_func = NULL;
	pip->in_progress_cmd = PIP_INVALID_CMD;
	pip->resp_data = NULL;
	pip->resp_len = NULL;

	cyapa->dev_pwr_mode = UNINIT_PWR_MODE;
	cyapa->dev_sleep_time = UNINIT_SLEEP_TIME;

	return 0;
}