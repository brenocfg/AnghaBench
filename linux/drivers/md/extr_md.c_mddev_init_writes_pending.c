#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ percpu_count_ptr; } ;
struct mddev {TYPE_1__ writes_pending; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PERCPU_REF_ALLOW_REINIT ; 
 int /*<<< orphan*/  no_op ; 
 scalar_t__ percpu_ref_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_ref_put (TYPE_1__*) ; 

int mddev_init_writes_pending(struct mddev *mddev)
{
	if (mddev->writes_pending.percpu_count_ptr)
		return 0;
	if (percpu_ref_init(&mddev->writes_pending, no_op,
			    PERCPU_REF_ALLOW_REINIT, GFP_KERNEL) < 0)
		return -ENOMEM;
	/* We want to start with the refcount at zero */
	percpu_ref_put(&mddev->writes_pending);
	return 0;
}