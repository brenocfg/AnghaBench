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
typedef  int /*<<< orphan*/  wait_queue_entry_t ;
struct i40iw_sc_dev {int vchnl_up; int /*<<< orphan*/  vf_reqs; struct i40iw_device* back_dev; } ;
struct i40iw_device {int /*<<< orphan*/  vchnl_msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_VCHNL_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  add_wait_queue_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wq_has_sleeper (int /*<<< orphan*/ *) ; 

bool i40iw_vf_clear_to_send(struct i40iw_sc_dev *dev)
{
	struct i40iw_device *iwdev;
	wait_queue_entry_t wait;

	iwdev = dev->back_dev;

	if (!wq_has_sleeper(&dev->vf_reqs) &&
	    (atomic_read(&iwdev->vchnl_msgs) == 0))
		return true; /* virtual channel is clear */

	init_wait(&wait);
	add_wait_queue_exclusive(&dev->vf_reqs, &wait);

	if (!wait_event_timeout(dev->vf_reqs,
				(atomic_read(&iwdev->vchnl_msgs) == 0),
				I40IW_VCHNL_EVENT_TIMEOUT))
		dev->vchnl_up = false;

	remove_wait_queue(&dev->vf_reqs, &wait);

	return dev->vchnl_up;
}