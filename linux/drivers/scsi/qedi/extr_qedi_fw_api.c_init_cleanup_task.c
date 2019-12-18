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
struct iscsi_task_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_TASK_TYPE_MIDPATH ; 
 int /*<<< orphan*/  init_sqe (struct iscsi_task_params*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int init_cleanup_task(struct iscsi_task_params *task_params)
{
	init_sqe(task_params, NULL, NULL, NULL, NULL, ISCSI_TASK_TYPE_MIDPATH,
		 true);
	return 0;
}