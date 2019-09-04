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
struct msc {int dummy; } ;
struct intel_th_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct msc* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_th_msc_deactivate (struct intel_th_device*) ; 
 int msc_buffer_free_unless_used (struct msc*) ; 

__attribute__((used)) static void intel_th_msc_remove(struct intel_th_device *thdev)
{
	struct msc *msc = dev_get_drvdata(&thdev->dev);
	int ret;

	intel_th_msc_deactivate(thdev);

	/*
	 * Buffers should not be used at this point except if the
	 * output character device is still open and the parent
	 * device gets detached from its bus, which is a FIXME.
	 */
	ret = msc_buffer_free_unless_used(msc);
	WARN_ON_ONCE(ret);
}