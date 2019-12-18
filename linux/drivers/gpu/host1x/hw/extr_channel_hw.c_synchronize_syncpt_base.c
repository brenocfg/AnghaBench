#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct host1x_syncpt {TYPE_3__* base; } ;
struct host1x_job {int syncpt_id; TYPE_2__* channel; } ;
struct host1x {struct host1x_syncpt* syncpt; } ;
struct TYPE_6__ {unsigned int id; } ;
struct TYPE_5__ {int /*<<< orphan*/  cdma; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_CLASS_HOST1X ; 
 int /*<<< orphan*/  HOST1X_UCLASS_LOAD_SYNCPT_BASE ; 
 int HOST1X_UCLASS_LOAD_SYNCPT_BASE_BASE_INDX_F (unsigned int) ; 
 int HOST1X_UCLASS_LOAD_SYNCPT_BASE_VALUE_F (int /*<<< orphan*/ ) ; 
 struct host1x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_cdma_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  host1x_opcode_setclass (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  host1x_syncpt_read_max (struct host1x_syncpt*) ; 

__attribute__((used)) static inline void synchronize_syncpt_base(struct host1x_job *job)
{
	struct host1x *host = dev_get_drvdata(job->channel->dev->parent);
	struct host1x_syncpt *sp = host->syncpt + job->syncpt_id;
	unsigned int id;
	u32 value;

	value = host1x_syncpt_read_max(sp);
	id = sp->base->id;

	host1x_cdma_push(&job->channel->cdma,
			 host1x_opcode_setclass(HOST1X_CLASS_HOST1X,
				HOST1X_UCLASS_LOAD_SYNCPT_BASE, 1),
			 HOST1X_UCLASS_LOAD_SYNCPT_BASE_BASE_INDX_F(id) |
			 HOST1X_UCLASS_LOAD_SYNCPT_BASE_VALUE_F(value));
}