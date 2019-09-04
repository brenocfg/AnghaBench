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
typedef  int u32 ;
struct host1x_job_gather {int base; int offset; int /*<<< orphan*/  bo; int /*<<< orphan*/  words; } ;
struct host1x_job {unsigned int num_gathers; struct host1x_job_gather* gathers; TYPE_1__* channel; } ;
struct host1x_cdma {int dummy; } ;
struct TYPE_2__ {struct host1x_cdma cdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  host1x_cdma_push (struct host1x_cdma*,int,int) ; 
 int host1x_opcode_gather (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_write_gather (struct host1x_cdma*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void submit_gathers(struct host1x_job *job)
{
	struct host1x_cdma *cdma = &job->channel->cdma;
	unsigned int i;

	for (i = 0; i < job->num_gathers; i++) {
		struct host1x_job_gather *g = &job->gathers[i];
		u32 op1 = host1x_opcode_gather(g->words);
		u32 op2 = g->base + g->offset;

		trace_write_gather(cdma, g->bo, g->offset, op1 & 0xffff);
		host1x_cdma_push(cdma, op1, op2);
	}
}