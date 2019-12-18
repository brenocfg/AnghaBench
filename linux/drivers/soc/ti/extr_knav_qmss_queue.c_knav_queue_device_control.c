#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct knav_queue_notify_config {int dummy; } ;
struct knav_queue {TYPE_2__* inst; } ;
typedef  enum knav_queue_ctrl_cmd { ____Placeholder_knav_queue_ctrl_cmd } knav_queue_ctrl_cmd ;
struct TYPE_4__ {int id; TYPE_1__* kdev; } ;
struct TYPE_3__ {int base_id; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  KNAV_QUEUE_DISABLE_NOTIFY 133 
#define  KNAV_QUEUE_ENABLE_NOTIFY 132 
#define  KNAV_QUEUE_FLUSH 131 
#define  KNAV_QUEUE_GET_COUNT 130 
#define  KNAV_QUEUE_GET_ID 129 
#define  KNAV_QUEUE_SET_NOTIFIER 128 
 int knav_queue_disable_notifier (struct knav_queue*) ; 
 int knav_queue_enable_notifier (struct knav_queue*) ; 
 int knav_queue_flush (struct knav_queue*) ; 
 int knav_queue_get_count (struct knav_queue*) ; 
 int knav_queue_set_notifier (struct knav_queue*,struct knav_queue_notify_config*) ; 

int knav_queue_device_control(void *qhandle, enum knav_queue_ctrl_cmd cmd,
				unsigned long arg)
{
	struct knav_queue *qh = qhandle;
	struct knav_queue_notify_config *cfg;
	int ret;

	switch ((int)cmd) {
	case KNAV_QUEUE_GET_ID:
		ret = qh->inst->kdev->base_id + qh->inst->id;
		break;

	case KNAV_QUEUE_FLUSH:
		ret = knav_queue_flush(qh);
		break;

	case KNAV_QUEUE_SET_NOTIFIER:
		cfg = (void *)arg;
		ret = knav_queue_set_notifier(qh, cfg);
		break;

	case KNAV_QUEUE_ENABLE_NOTIFY:
		ret = knav_queue_enable_notifier(qh);
		break;

	case KNAV_QUEUE_DISABLE_NOTIFY:
		ret = knav_queue_disable_notifier(qh);
		break;

	case KNAV_QUEUE_GET_COUNT:
		ret = knav_queue_get_count(qh);
		break;

	default:
		ret = -ENOTSUPP;
		break;
	}
	return ret;
}