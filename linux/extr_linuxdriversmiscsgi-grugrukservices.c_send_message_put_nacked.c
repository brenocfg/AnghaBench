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
struct gru_message_queue_desc {int mq_gpa; int /*<<< orphan*/  interrupt_vector; } ;

/* Variables and functions */
 scalar_t__ CBS_IDLE ; 
 int /*<<< orphan*/  IMA ; 
 int MQE_CONGESTION ; 
 int MQE_OK ; 
 int MQE_UNEXPECTED_CB_ERR ; 
 int MQIE_AGAIN ; 
 int /*<<< orphan*/  XTYPE_CL ; 
 int gru_get_amo_value_head (void*) ; 
 int /*<<< orphan*/  gru_get_tri (void*) ; 
 int /*<<< orphan*/  gru_vset (void*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_vstore (void*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gru_wait (void*) ; 
 int send_noop_message (void*,struct gru_message_queue_desc*,void*) ; 

__attribute__((used)) static int send_message_put_nacked(void *cb, struct gru_message_queue_desc *mqd,
			void *mesg, int lines)
{
	unsigned long m;
	int ret, loops = 200;	/* experimentally determined */

	m = mqd->mq_gpa + (gru_get_amo_value_head(cb) << 6);
	if (lines == 2) {
		gru_vset(cb, m, 0, XTYPE_CL, lines, 1, IMA);
		if (gru_wait(cb) != CBS_IDLE)
			return MQE_UNEXPECTED_CB_ERR;
	}
	gru_vstore(cb, m, gru_get_tri(mesg), XTYPE_CL, lines, 1, IMA);
	if (gru_wait(cb) != CBS_IDLE)
		return MQE_UNEXPECTED_CB_ERR;

	if (!mqd->interrupt_vector)
		return MQE_OK;

	/*
	 * Send a noop message in order to deliver a cross-partition interrupt
	 * to the SSI that contains the target message queue. Normally, the
	 * interrupt is automatically delivered by hardware following mesq
	 * operations, but some error conditions require explicit delivery.
	 * The noop message will trigger delivery. Otherwise partition failures
	 * could cause unrecovered errors.
	 */
	do {
		ret = send_noop_message(cb, mqd, mesg);
	} while ((ret == MQIE_AGAIN || ret == MQE_CONGESTION) && (loops-- > 0));

	if (ret == MQIE_AGAIN || ret == MQE_CONGESTION) {
		/*
		 * Don't indicate to the app to resend the message, as it's
		 * already been successfully sent.  We simply send an OK
		 * (rather than fail the send with MQE_UNEXPECTED_CB_ERR),
		 * assuming that the other side is receiving enough
		 * interrupts to get this message processed anyway.
		 */
		ret = MQE_OK;
	}
	return ret;
}