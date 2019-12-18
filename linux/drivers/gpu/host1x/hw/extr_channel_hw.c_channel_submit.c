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
typedef  int /*<<< orphan*/  u32 ;
struct host1x_waitlist {int dummy; } ;
struct host1x_syncpt {scalar_t__ base; } ;
struct host1x_job {int syncpt_id; scalar_t__ class; int /*<<< orphan*/  syncpt_end; scalar_t__ serialize; int /*<<< orphan*/  syncpt_incrs; int /*<<< orphan*/  num_relocs; int /*<<< orphan*/  num_gathers; struct host1x_channel* channel; } ;
struct host1x_channel {int /*<<< orphan*/  submitlock; TYPE_1__* dev; int /*<<< orphan*/  cdma; } ;
struct host1x {struct host1x_syncpt* syncpt; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HOST1X_CLASS_HOST1X ; 
 int /*<<< orphan*/  HOST1X_INTR_ACTION_SUBMIT_COMPLETE ; 
 int /*<<< orphan*/  HOST1X_OPCODE_NOP ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct host1x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int host1x_cdma_begin (int /*<<< orphan*/ *,struct host1x_job*) ; 
 int /*<<< orphan*/  host1x_cdma_end (int /*<<< orphan*/ *,struct host1x_job*) ; 
 int /*<<< orphan*/  host1x_cdma_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_channel_set_streamid (struct host1x_channel*) ; 
 int /*<<< orphan*/  host1x_class_host_wait_syncpt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_hw_syncpt_assign_to_channel (struct host1x*,struct host1x_syncpt*,struct host1x_channel*) ; 
 int host1x_intr_add_action (struct host1x*,struct host1x_syncpt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct host1x_channel*,struct host1x_waitlist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host1x_opcode_setclass (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  host1x_syncpt_incr_max (struct host1x_syncpt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_syncpt_read_max (struct host1x_syncpt*) ; 
 int /*<<< orphan*/  host1x_uclass_wait_syncpt_r () ; 
 int /*<<< orphan*/  kfree (struct host1x_waitlist*) ; 
 struct host1x_waitlist* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_gathers (struct host1x_job*) ; 
 int /*<<< orphan*/  synchronize_syncpt_base (struct host1x_job*) ; 
 int /*<<< orphan*/  trace_host1x_channel_submit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_host1x_channel_submitted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int channel_submit(struct host1x_job *job)
{
	struct host1x_channel *ch = job->channel;
	struct host1x_syncpt *sp;
	u32 user_syncpt_incrs = job->syncpt_incrs;
	u32 prev_max = 0;
	u32 syncval;
	int err;
	struct host1x_waitlist *completed_waiter = NULL;
	struct host1x *host = dev_get_drvdata(ch->dev->parent);

	sp = host->syncpt + job->syncpt_id;
	trace_host1x_channel_submit(dev_name(ch->dev),
				    job->num_gathers, job->num_relocs,
				    job->syncpt_id, job->syncpt_incrs);

	/* before error checks, return current max */
	prev_max = job->syncpt_end = host1x_syncpt_read_max(sp);

	/* get submit lock */
	err = mutex_lock_interruptible(&ch->submitlock);
	if (err)
		goto error;

	completed_waiter = kzalloc(sizeof(*completed_waiter), GFP_KERNEL);
	if (!completed_waiter) {
		mutex_unlock(&ch->submitlock);
		err = -ENOMEM;
		goto error;
	}

	host1x_channel_set_streamid(ch);

	/* begin a CDMA submit */
	err = host1x_cdma_begin(&ch->cdma, job);
	if (err) {
		mutex_unlock(&ch->submitlock);
		goto error;
	}

	if (job->serialize) {
		/*
		 * Force serialization by inserting a host wait for the
		 * previous job to finish before this one can commence.
		 */
		host1x_cdma_push(&ch->cdma,
				 host1x_opcode_setclass(HOST1X_CLASS_HOST1X,
					host1x_uclass_wait_syncpt_r(), 1),
				 host1x_class_host_wait_syncpt(job->syncpt_id,
					host1x_syncpt_read_max(sp)));
	}

	/* Synchronize base register to allow using it for relative waiting */
	if (sp->base)
		synchronize_syncpt_base(job);

	syncval = host1x_syncpt_incr_max(sp, user_syncpt_incrs);

	host1x_hw_syncpt_assign_to_channel(host, sp, ch);

	job->syncpt_end = syncval;

	/* add a setclass for modules that require it */
	if (job->class)
		host1x_cdma_push(&ch->cdma,
				 host1x_opcode_setclass(job->class, 0, 0),
				 HOST1X_OPCODE_NOP);

	submit_gathers(job);

	/* end CDMA submit & stash pinned hMems into sync queue */
	host1x_cdma_end(&ch->cdma, job);

	trace_host1x_channel_submitted(dev_name(ch->dev), prev_max, syncval);

	/* schedule a submit complete interrupt */
	err = host1x_intr_add_action(host, sp, syncval,
				     HOST1X_INTR_ACTION_SUBMIT_COMPLETE, ch,
				     completed_waiter, NULL);
	completed_waiter = NULL;
	WARN(err, "Failed to set submit complete interrupt");

	mutex_unlock(&ch->submitlock);

	return 0;

error:
	kfree(completed_waiter);
	return err;
}