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
struct zcrypt_queue {int online; int /*<<< orphan*/  reply; int /*<<< orphan*/  load; struct ap_queue* queue; int /*<<< orphan*/  ops; } ;
struct ap_queue {struct zcrypt_queue* private; int /*<<< orphan*/  request_timeout; } ;
struct ap_device {int device_type; int /*<<< orphan*/  device; } ;

/* Variables and functions */
#define  AP_DEVICE_TYPE_CEX2A 129 
#define  AP_DEVICE_TYPE_CEX3A 128 
 int /*<<< orphan*/  CEX2A_CLEANUP_TIME ; 
 int /*<<< orphan*/  CEX2A_MAX_RESPONSE_SIZE ; 
 int /*<<< orphan*/  CEX3A_MAX_RESPONSE_SIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MSGTYPE50_NAME ; 
 int /*<<< orphan*/  MSGTYPE50_VARIANT_DEFAULT ; 
 int /*<<< orphan*/  ap_queue_init_reply (struct ap_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ap_queue* to_ap_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_msgtype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zcrypt_queue* zcrypt_queue_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcrypt_queue_free (struct zcrypt_queue*) ; 
 int zcrypt_queue_register (struct zcrypt_queue*) ; 

__attribute__((used)) static int zcrypt_cex2a_queue_probe(struct ap_device *ap_dev)
{
	struct ap_queue *aq = to_ap_queue(&ap_dev->device);
	struct zcrypt_queue *zq = NULL;
	int rc;

	switch (ap_dev->device_type) {
	case AP_DEVICE_TYPE_CEX2A:
		zq = zcrypt_queue_alloc(CEX2A_MAX_RESPONSE_SIZE);
		if (!zq)
			return -ENOMEM;
		break;
	case AP_DEVICE_TYPE_CEX3A:
		zq = zcrypt_queue_alloc(CEX3A_MAX_RESPONSE_SIZE);
		if (!zq)
			return -ENOMEM;
		break;
	}
	if (!zq)
		return -ENODEV;
	zq->ops = zcrypt_msgtype(MSGTYPE50_NAME, MSGTYPE50_VARIANT_DEFAULT);
	zq->queue = aq;
	zq->online = 1;
	atomic_set(&zq->load, 0);
	ap_queue_init_reply(aq, &zq->reply);
	aq->request_timeout = CEX2A_CLEANUP_TIME,
	aq->private = zq;
	rc = zcrypt_queue_register(zq);
	if (rc) {
		aq->private = NULL;
		zcrypt_queue_free(zq);
	}

	return rc;
}