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
struct fcoe_task_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_FCOE_ABTS_REQUEST ; 
 int /*<<< orphan*/  init_common_sqe (struct fcoe_task_params*,int /*<<< orphan*/ ) ; 

int init_initiator_abort_fcoe_task(struct fcoe_task_params *task_params)
{
	init_common_sqe(task_params, SEND_FCOE_ABTS_REQUEST);
	return 0;
}