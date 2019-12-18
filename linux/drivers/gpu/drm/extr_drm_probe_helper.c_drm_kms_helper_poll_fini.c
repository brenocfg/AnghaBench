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
struct TYPE_2__ {int poll_enabled; int /*<<< orphan*/  output_poll_work; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

void drm_kms_helper_poll_fini(struct drm_device *dev)
{
	if (!dev->mode_config.poll_enabled)
		return;

	dev->mode_config.poll_enabled = false;
	cancel_delayed_work_sync(&dev->mode_config.output_poll_work);
}