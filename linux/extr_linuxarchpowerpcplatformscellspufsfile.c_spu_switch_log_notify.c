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
typedef  void* u32 ;
struct switch_log_entry {int spu_id; void* val; void* type; int /*<<< orphan*/  timebase; int /*<<< orphan*/  tstamp; } ;
struct spu_context {TYPE_1__* switch_log; } ;
struct spu {int number; } ;
struct TYPE_2__ {int head; int /*<<< orphan*/  wait; struct switch_log_entry* log; } ;

/* Variables and functions */
 int SWITCH_LOG_BUFSIZE ; 
 int /*<<< orphan*/  get_tb () ; 
 int /*<<< orphan*/  ktime_get_ts64 (int /*<<< orphan*/ *) ; 
 int spufs_switch_log_avail (struct spu_context*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void spu_switch_log_notify(struct spu *spu, struct spu_context *ctx,
		u32 type, u32 val)
{
	if (!ctx->switch_log)
		return;

	if (spufs_switch_log_avail(ctx) > 1) {
		struct switch_log_entry *p;

		p = ctx->switch_log->log + ctx->switch_log->head;
		ktime_get_ts64(&p->tstamp);
		p->timebase = get_tb();
		p->spu_id = spu ? spu->number : -1;
		p->type = type;
		p->val = val;

		ctx->switch_log->head =
			(ctx->switch_log->head + 1) % SWITCH_LOG_BUFSIZE;
	}

	wake_up(&ctx->switch_log->wait);
}