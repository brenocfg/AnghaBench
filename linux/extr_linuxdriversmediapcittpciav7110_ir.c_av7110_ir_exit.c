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
struct TYPE_2__ {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  ir_tasklet; int /*<<< orphan*/ * ir_handler; int /*<<< orphan*/  keyup_timer; } ;
struct av7110 {TYPE_1__ ir; } ;

/* Variables and functions */
 int av_cnt ; 
 struct av7110** av_list ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void av7110_ir_exit(struct av7110 *av7110)
{
	int i;

	if (av_cnt == 0)
		return;

	del_timer_sync(&av7110->ir.keyup_timer);
	av7110->ir.ir_handler = NULL;
	tasklet_kill(&av7110->ir.ir_tasklet);

	for (i = 0; i < av_cnt; i++)
		if (av_list[i] == av7110) {
			av_list[i] = av_list[av_cnt-1];
			av_list[av_cnt-1] = NULL;
			break;
		}

	if (av_cnt == 1)
		remove_proc_entry("av7110_ir", NULL);

	input_unregister_device(av7110->ir.input_dev);

	av_cnt--;
}