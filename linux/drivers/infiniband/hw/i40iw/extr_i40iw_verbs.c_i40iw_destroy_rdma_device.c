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
struct i40iw_ib_device {int /*<<< orphan*/  ibdev; TYPE_1__* iwdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_count; int /*<<< orphan*/  close_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void i40iw_destroy_rdma_device(struct i40iw_ib_device *iwibdev)
{
	ib_unregister_device(&iwibdev->ibdev);
	wait_event_timeout(iwibdev->iwdev->close_wq,
			   !atomic64_read(&iwibdev->iwdev->use_count),
			   I40IW_EVENT_TIMEOUT);
	ib_dealloc_device(&iwibdev->ibdev);
}