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
struct data_queue {int qid; TYPE_3__* rt2x00dev; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_2__* ops; int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__* lib; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* kick_queue ) (struct data_queue*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_PRESENT ; 
#define  QID_AC_BE 132 
#define  QID_AC_BK 131 
#define  QID_AC_VI 130 
#define  QID_AC_VO 129 
#define  QID_RX 128 
 int /*<<< orphan*/  QUEUE_PAUSED ; 
 int /*<<< orphan*/  QUEUE_STARTED ; 
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct data_queue*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00queue_unpause_queue(struct data_queue *queue)
{
	if (!test_bit(DEVICE_STATE_PRESENT, &queue->rt2x00dev->flags) ||
	    !test_bit(QUEUE_STARTED, &queue->flags) ||
	    !test_and_clear_bit(QUEUE_PAUSED, &queue->flags))
		return;

	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		/*
		 * For TX queues, we have to enable the queue
		 * inside mac80211.
		 */
		ieee80211_wake_queue(queue->rt2x00dev->hw, queue->qid);
		break;
	case QID_RX:
		/*
		 * For RX we need to kick the queue now in order to
		 * receive frames.
		 */
		queue->rt2x00dev->ops->lib->kick_queue(queue);
	default:
		break;
	}
}