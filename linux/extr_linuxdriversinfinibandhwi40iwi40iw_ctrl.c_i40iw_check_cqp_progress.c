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
struct i40iw_sc_dev {scalar_t__* cqp_cmd_stats; } ;
struct i40iw_cqp_timeout {scalar_t__ compl_cqp_cmds; scalar_t__ count; } ;

/* Variables and functions */
 size_t OP_COMPLETED_COMMANDS ; 
 size_t OP_REQUESTED_COMMANDS ; 

void i40iw_check_cqp_progress(struct i40iw_cqp_timeout *cqp_timeout, struct i40iw_sc_dev *dev)
{
	if (cqp_timeout->compl_cqp_cmds != dev->cqp_cmd_stats[OP_COMPLETED_COMMANDS]) {
		cqp_timeout->compl_cqp_cmds = dev->cqp_cmd_stats[OP_COMPLETED_COMMANDS];
		cqp_timeout->count = 0;
	} else {
		if (dev->cqp_cmd_stats[OP_REQUESTED_COMMANDS] != cqp_timeout->compl_cqp_cmds)
			cqp_timeout->count++;
	}
}