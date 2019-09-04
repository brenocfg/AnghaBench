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
typedef  scalar_t__ u16 ;
struct capilib_ncci {int /*<<< orphan*/  nmsg; struct capilib_msgidqueue* msgidfree; struct capilib_msgidqueue* msgidlast; struct capilib_msgidqueue* msgidqueue; } ;
struct capilib_msgidqueue {scalar_t__ msgid; struct capilib_msgidqueue* next; } ;

/* Variables and functions */

__attribute__((used)) static inline int mq_dequeue(struct capilib_ncci *np, u16 msgid)
{
	struct capilib_msgidqueue **pp;
	for (pp = &np->msgidqueue; *pp; pp = &(*pp)->next) {
		if ((*pp)->msgid == msgid) {
			struct capilib_msgidqueue *mq = *pp;
			*pp = mq->next;
			if (mq == np->msgidlast)
				np->msgidlast = NULL;
			mq->next = np->msgidfree;
			np->msgidfree = mq;
			np->nmsg--;
			return 1;
		}
	}
	return 0;
}