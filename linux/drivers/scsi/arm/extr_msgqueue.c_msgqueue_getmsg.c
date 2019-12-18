#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct message {int dummy; } ;
struct msgqueue_entry {struct message msg; struct msgqueue_entry* next; } ;
struct TYPE_3__ {struct msgqueue_entry* qe; } ;
typedef  TYPE_1__ MsgQueue_t ;

/* Variables and functions */

struct message *msgqueue_getmsg(MsgQueue_t *msgq, int msgno)
{
	struct msgqueue_entry *mq;

	for (mq = msgq->qe; mq && msgno; mq = mq->next, msgno--);

	return mq ? &mq->msg : NULL;
}