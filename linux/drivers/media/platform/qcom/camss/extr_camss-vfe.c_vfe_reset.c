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
struct vfe_device {TYPE_2__* camss; int /*<<< orphan*/  reset_complete; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* global_reset ) (struct vfe_device*) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  VFE_RESET_TIMEOUT_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vfe_device*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfe_reset(struct vfe_device *vfe)
{
	unsigned long time;

	reinit_completion(&vfe->reset_complete);

	vfe->ops->global_reset(vfe);

	time = wait_for_completion_timeout(&vfe->reset_complete,
		msecs_to_jiffies(VFE_RESET_TIMEOUT_MS));
	if (!time) {
		dev_err(vfe->camss->dev, "VFE reset timeout\n");
		return -EIO;
	}

	return 0;
}