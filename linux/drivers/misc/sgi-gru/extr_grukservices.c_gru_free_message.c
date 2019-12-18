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
struct message_queue {void* limit; void* start2; int* hstatus; struct message_header* next; void* start; } ;
struct message_header {int lines; int /*<<< orphan*/  present; } ;
struct gru_message_queue_desc {struct message_queue* mq; } ;

/* Variables and functions */
 int GRU_CACHE_LINE_BYTES ; 
 int /*<<< orphan*/  MQS_EMPTY ; 
 int /*<<< orphan*/  restore_present2 (struct message_header*,int /*<<< orphan*/ ) ; 

void gru_free_message(struct gru_message_queue_desc *mqd, void *mesg)
{
	struct message_queue *mq = mqd->mq;
	struct message_header *mhdr = mq->next;
	void *next, *pnext;
	int half = -1;
	int lines = mhdr->lines;

	if (lines == 2)
		restore_present2(mhdr, MQS_EMPTY);
	mhdr->present = MQS_EMPTY;

	pnext = mq->next;
	next = pnext + GRU_CACHE_LINE_BYTES * lines;
	if (next == mq->limit) {
		next = mq->start;
		half = 1;
	} else if (pnext < mq->start2 && next >= mq->start2) {
		half = 0;
	}

	if (half >= 0)
		mq->hstatus[half] = 1;
	mq->next = next;
}