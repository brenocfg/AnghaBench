#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct a6xx_hfi_msg_perf_table {int num_gpu_levels; int num_gmu_levels; TYPE_2__* cx_votes; TYPE_1__* gx_votes; int /*<<< orphan*/  member_0; } ;
struct a6xx_gmu {int nr_gpu_freqs; int nr_gmu_freqs; int* gpu_freqs; int* gmu_freqs; int /*<<< orphan*/ * cx_arc_votes; int /*<<< orphan*/ * gx_arc_votes; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_4__ {int freq; int /*<<< orphan*/  vote; } ;
struct TYPE_3__ {int freq; int /*<<< orphan*/  vote; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_H2F_MSG_PERF_TABLE ; 
 int a6xx_hfi_send_msg (struct a6xx_gmu*,int /*<<< orphan*/ ,struct a6xx_hfi_msg_perf_table*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a6xx_hfi_send_perf_table(struct a6xx_gmu *gmu)
{
	struct a6xx_hfi_msg_perf_table msg = { 0 };
	int i;

	msg.num_gpu_levels = gmu->nr_gpu_freqs;
	msg.num_gmu_levels = gmu->nr_gmu_freqs;

	for (i = 0; i < gmu->nr_gpu_freqs; i++) {
		msg.gx_votes[i].vote = gmu->gx_arc_votes[i];
		msg.gx_votes[i].freq = gmu->gpu_freqs[i] / 1000;
	}

	for (i = 0; i < gmu->nr_gmu_freqs; i++) {
		msg.cx_votes[i].vote = gmu->cx_arc_votes[i];
		msg.cx_votes[i].freq = gmu->gmu_freqs[i] / 1000;
	}

	return a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_PERF_TABLE, &msg, sizeof(msg),
		NULL, 0);
}