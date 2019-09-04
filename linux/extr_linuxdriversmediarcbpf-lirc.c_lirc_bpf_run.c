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
typedef  int /*<<< orphan*/  u32 ;
struct rc_dev {struct ir_raw_event_ctrl* raw; } ;
struct ir_raw_event_ctrl {int /*<<< orphan*/  bpf_sample; scalar_t__ progs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_RUN ; 
 int /*<<< orphan*/  BPF_PROG_RUN_ARRAY (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void lirc_bpf_run(struct rc_dev *rcdev, u32 sample)
{
	struct ir_raw_event_ctrl *raw = rcdev->raw;

	raw->bpf_sample = sample;

	if (raw->progs)
		BPF_PROG_RUN_ARRAY(raw->progs, &raw->bpf_sample, BPF_PROG_RUN);
}