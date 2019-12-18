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
union gru_mesqhead {int /*<<< orphan*/  val; } ;
struct gru_message_queue_desc {int qlines; int /*<<< orphan*/  mq_gpa; } ;

/* Variables and functions */
 scalar_t__ CBS_IDLE ; 
 int /*<<< orphan*/  EOP_ERR_CSWAP ; 
 int /*<<< orphan*/  EOP_IR_CLR ; 
 int /*<<< orphan*/  EOP_IR_INC ; 
 int /*<<< orphan*/  HSTATUS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IMA ; 
 int MQE_QUEUE_FULL ; 
 int MQE_UNEXPECTED_CB_ERR ; 
 int MQIE_AGAIN ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XTYPE_DW ; 
 int /*<<< orphan*/  gru_gamer (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_gamir (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long gru_get_amo_value (void*) ; 
 unsigned int gru_get_amo_value_head (void*) ; 
 unsigned int gru_get_amo_value_limit (void*) ; 
 union gru_mesqhead gru_mesq_head (int,int) ; 
 scalar_t__ gru_wait (void*) ; 
 int /*<<< orphan*/  mesq_qf_locked ; 
 int /*<<< orphan*/  mesq_qf_noop_not_full ; 
 int /*<<< orphan*/  mesq_qf_switch_head_failed ; 
 int /*<<< orphan*/  mesq_qf_unexpected_error ; 
 scalar_t__ send_noop_message (void*,struct gru_message_queue_desc*,void*) ; 

__attribute__((used)) static int send_message_queue_full(void *cb, struct gru_message_queue_desc *mqd,
				void *mesg, int lines)
{
	union gru_mesqhead mqh;
	unsigned int limit, head;
	unsigned long avalue;
	int half, qlines;

	/* Determine if switching to first/second half of q */
	avalue = gru_get_amo_value(cb);
	head = gru_get_amo_value_head(cb);
	limit = gru_get_amo_value_limit(cb);

	qlines = mqd->qlines;
	half = (limit != qlines);

	if (half)
		mqh = gru_mesq_head(qlines / 2 + 1, qlines);
	else
		mqh = gru_mesq_head(2, qlines / 2 + 1);

	/* Try to get lock for switching head pointer */
	gru_gamir(cb, EOP_IR_CLR, HSTATUS(mqd->mq_gpa, half), XTYPE_DW, IMA);
	if (gru_wait(cb) != CBS_IDLE)
		goto cberr;
	if (!gru_get_amo_value(cb)) {
		STAT(mesq_qf_locked);
		return MQE_QUEUE_FULL;
	}

	/* Got the lock. Send optional NOP if queue not full, */
	if (head != limit) {
		if (send_noop_message(cb, mqd, mesg)) {
			gru_gamir(cb, EOP_IR_INC, HSTATUS(mqd->mq_gpa, half),
					XTYPE_DW, IMA);
			if (gru_wait(cb) != CBS_IDLE)
				goto cberr;
			STAT(mesq_qf_noop_not_full);
			return MQIE_AGAIN;
		}
		avalue++;
	}

	/* Then flip queuehead to other half of queue. */
	gru_gamer(cb, EOP_ERR_CSWAP, mqd->mq_gpa, XTYPE_DW, mqh.val, avalue,
							IMA);
	if (gru_wait(cb) != CBS_IDLE)
		goto cberr;

	/* If not successfully in swapping queue head, clear the hstatus lock */
	if (gru_get_amo_value(cb) != avalue) {
		STAT(mesq_qf_switch_head_failed);
		gru_gamir(cb, EOP_IR_INC, HSTATUS(mqd->mq_gpa, half), XTYPE_DW,
							IMA);
		if (gru_wait(cb) != CBS_IDLE)
			goto cberr;
	}
	return MQIE_AGAIN;
cberr:
	STAT(mesq_qf_unexpected_error);
	return MQE_UNEXPECTED_CB_ERR;
}