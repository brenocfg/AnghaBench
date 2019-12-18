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
struct venus_inst {scalar_t__ session_type; int /*<<< orphan*/  delayed_process_work; int /*<<< orphan*/  delayed_process; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ VIDC_SESSION_TYPE_DEC ; 
 int /*<<< orphan*/  delayed_process_buf_func ; 

void venus_helper_init_instance(struct venus_inst *inst)
{
	if (inst->session_type == VIDC_SESSION_TYPE_DEC) {
		INIT_LIST_HEAD(&inst->delayed_process);
		INIT_WORK(&inst->delayed_process_work,
			  delayed_process_buf_func);
	}
}