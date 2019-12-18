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
struct qeth_card {int dummy; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,unsigned int) ; 
 scalar_t__ qeth_is_cq (struct qeth_card*,int) ; 
 int /*<<< orphan*/  qeth_qdio_cq_handler (struct qeth_card*,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  qeth_schedule_recovery (struct qeth_card*) ; 

__attribute__((used)) static void qeth_qdio_input_handler(struct ccw_device *ccwdev,
				    unsigned int qdio_err, int queue,
				    int first_elem, int count,
				    unsigned long card_ptr)
{
	struct qeth_card *card = (struct qeth_card *)card_ptr;

	QETH_CARD_TEXT_(card, 2, "qihq%d", queue);
	QETH_CARD_TEXT_(card, 2, "qiec%d", qdio_err);

	if (qeth_is_cq(card, queue))
		qeth_qdio_cq_handler(card, qdio_err, queue, first_elem, count);
	else if (qdio_err)
		qeth_schedule_recovery(card);
}