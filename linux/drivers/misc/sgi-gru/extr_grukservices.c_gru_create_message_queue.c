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
struct message_queue {unsigned int qlines; int* hstatus; int /*<<< orphan*/  head; int /*<<< orphan*/  data; int /*<<< orphan*/ * limit; int /*<<< orphan*/ * next; int /*<<< orphan*/ * start2; int /*<<< orphan*/ * start; } ;
struct gru_message_queue_desc {unsigned int qlines; int interrupt_pnode; int interrupt_vector; int interrupt_apicid; int /*<<< orphan*/  mq_gpa; struct message_queue* mq; } ;

/* Variables and functions */
 unsigned int GRU_CACHE_LINE_BYTES ; 
 int /*<<< orphan*/  gru_mesq_head (int,unsigned int) ; 
 int /*<<< orphan*/  memset (struct message_queue*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  uv_gpa (struct message_queue*) ; 

int gru_create_message_queue(struct gru_message_queue_desc *mqd,
		void *p, unsigned int bytes, int nasid, int vector, int apicid)
{
	struct message_queue *mq = p;
	unsigned int qlines;

	qlines = bytes / GRU_CACHE_LINE_BYTES - 2;
	memset(mq, 0, bytes);
	mq->start = &mq->data;
	mq->start2 = &mq->data + (qlines / 2 - 1) * GRU_CACHE_LINE_BYTES;
	mq->next = &mq->data;
	mq->limit = &mq->data + (qlines - 2) * GRU_CACHE_LINE_BYTES;
	mq->qlines = qlines;
	mq->hstatus[0] = 0;
	mq->hstatus[1] = 1;
	mq->head = gru_mesq_head(2, qlines / 2 + 1);
	mqd->mq = mq;
	mqd->mq_gpa = uv_gpa(mq);
	mqd->qlines = qlines;
	mqd->interrupt_pnode = nasid >> 1;
	mqd->interrupt_vector = vector;
	mqd->interrupt_apicid = apicid;
	return 0;
}