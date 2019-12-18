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
typedef  scalar_t__ u32 ;
struct host1x_job_gather {int /*<<< orphan*/  words; scalar_t__ offset; int /*<<< orphan*/  bo; scalar_t__ base; } ;
struct host1x_job {unsigned int num_gathers; struct host1x_job_gather* gathers; TYPE_1__* channel; } ;
struct host1x_cdma {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {struct device* dev; struct host1x_cdma cdma; } ;

/* Variables and functions */
 scalar_t__ HOST1X_OPCODE_NOP ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  host1x_cdma_push (struct host1x_cdma*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  host1x_cdma_push_wide (struct host1x_cdma*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ host1x_opcode_gather (int /*<<< orphan*/ ) ; 
 scalar_t__ host1x_opcode_gather_wide (int /*<<< orphan*/ ) ; 
 scalar_t__ lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  trace_write_gather (struct host1x_cdma*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void submit_gathers(struct host1x_job *job)
{
	struct host1x_cdma *cdma = &job->channel->cdma;
#if HOST1X_HW < 6
	struct device *dev = job->channel->dev;
#endif
	unsigned int i;

	for (i = 0; i < job->num_gathers; i++) {
		struct host1x_job_gather *g = &job->gathers[i];
		dma_addr_t addr = g->base + g->offset;
		u32 op2, op3;

		op2 = lower_32_bits(addr);
		op3 = upper_32_bits(addr);

		trace_write_gather(cdma, g->bo, g->offset, g->words);

		if (op3 != 0) {
#if HOST1X_HW >= 6
			u32 op1 = host1x_opcode_gather_wide(g->words);
			u32 op4 = HOST1X_OPCODE_NOP;

			host1x_cdma_push_wide(cdma, op1, op2, op3, op4);
#else
			dev_err(dev, "invalid gather for push buffer %pad\n",
				&addr);
			continue;
#endif
		} else {
			u32 op1 = host1x_opcode_gather(g->words);

			host1x_cdma_push(cdma, op1, op2);
		}
	}
}