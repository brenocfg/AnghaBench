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
typedef  void* u8 ;
struct rave_sp_reply {void* data; size_t length; int /*<<< orphan*/  received; int /*<<< orphan*/  code; void* ackid; } ;
struct rave_sp {int /*<<< orphan*/  bus_lock; int /*<<< orphan*/  reply_lock; struct rave_sp_reply* reply; TYPE_3__* serdev; int /*<<< orphan*/  ackid; TYPE_2__* variant; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int (* translate ) (unsigned char) ;} ;
struct TYPE_5__ {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLETION_INITIALIZER_ONSTACK (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 void* atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rave_sp_reply_code (void*) ; 
 int /*<<< orphan*/  rave_sp_write (struct rave_sp*,unsigned char*,size_t) ; 
 int stub1 (unsigned char) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int rave_sp_exec(struct rave_sp *sp,
		 void *__data,  size_t data_size,
		 void *reply_data, size_t reply_data_size)
{
	struct rave_sp_reply reply = {
		.data     = reply_data,
		.length   = reply_data_size,
		.received = COMPLETION_INITIALIZER_ONSTACK(reply.received),
	};
	unsigned char *data = __data;
	int command, ret = 0;
	u8 ackid;

	command = sp->variant->cmd.translate(data[0]);
	if (command < 0)
		return command;

	ackid       = atomic_inc_return(&sp->ackid);
	reply.ackid = ackid;
	reply.code  = rave_sp_reply_code((u8)command),

	mutex_lock(&sp->bus_lock);

	mutex_lock(&sp->reply_lock);
	sp->reply = &reply;
	mutex_unlock(&sp->reply_lock);

	data[0] = command;
	data[1] = ackid;

	rave_sp_write(sp, data, data_size);

	if (!wait_for_completion_timeout(&reply.received, HZ)) {
		dev_err(&sp->serdev->dev, "Command timeout\n");
		ret = -ETIMEDOUT;

		mutex_lock(&sp->reply_lock);
		sp->reply = NULL;
		mutex_unlock(&sp->reply_lock);
	}

	mutex_unlock(&sp->bus_lock);
	return ret;
}