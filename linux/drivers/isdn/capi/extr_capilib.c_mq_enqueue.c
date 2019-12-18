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
typedef  int /*<<< orphan*/  u16 ;
struct capilib_ncci {int /*<<< orphan*/  nmsg; struct capilib_msgidqueue* msgidqueue; struct capilib_msgidqueue* msgidlast; struct capilib_msgidqueue* msgidfree; } ;
struct capilib_msgidqueue {struct capilib_msgidqueue* next; int /*<<< orphan*/  msgid; } ;

/* Variables and functions */

__attribute__((used)) static inline int mq_enqueue(struct capilib_ncci *np, u16 msgid)
{
	struct capilib_msgidqueue *mq;
	if ((mq = np->msgidfree) == NULL)
		return 0;
	np->msgidfree = mq->next;
	mq->msgid = msgid;
	mq->next = NULL;
	if (np->msgidlast)
		np->msgidlast->next = mq;
	np->msgidlast = mq;
	if (!np->msgidqueue)
		np->msgidqueue = mq;
	np->nmsg++;
	return 1;
}