#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct hpsa_scsi_dev_t {int /*<<< orphan*/  scsi3addr; int /*<<< orphan*/  commands_outstanding; } ;
struct ctlr_info {int /*<<< orphan*/  reset_mutex; TYPE_1__* pdev; int /*<<< orphan*/  event_sync_wait_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINTR ; 
 int ENODEV ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int hpsa_send_reset (struct ctlr_info*,struct hpsa_scsi_dev_t*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lockup_detected (struct ctlr_info*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (scalar_t__) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int wait_for_device_to_become_ready (struct ctlr_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_do_reset(struct ctlr_info *h, struct hpsa_scsi_dev_t *dev,
	u8 reset_type, int reply_queue)
{
	int rc = 0;

	/* We can really only handle one reset at a time */
	if (mutex_lock_interruptible(&h->reset_mutex) == -EINTR) {
		dev_warn(&h->pdev->dev, "concurrent reset wait interrupted.\n");
		return -EINTR;
	}

	rc = hpsa_send_reset(h, dev, reset_type, reply_queue);
	if (!rc) {
		/* incremented by sending the reset request */
		atomic_dec(&dev->commands_outstanding);
		wait_event(h->event_sync_wait_queue,
			atomic_read(&dev->commands_outstanding) <= 0 ||
			lockup_detected(h));
	}

	if (unlikely(lockup_detected(h))) {
		dev_warn(&h->pdev->dev,
			 "Controller lockup detected during reset wait\n");
		rc = -ENODEV;
	}

	if (!rc)
		rc = wait_for_device_to_become_ready(h, dev->scsi3addr, 0);

	mutex_unlock(&h->reset_mutex);
	return rc;
}