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
struct drm_device {TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int (* get_vblank_timestamp ) (struct drm_device*,unsigned int,int*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 scalar_t__ drm_timestamp_precision ; 
 int /*<<< orphan*/  ktime_get () ; 
 int stub1 (struct drm_device*,unsigned int,int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
drm_get_last_vbltimestamp(struct drm_device *dev, unsigned int pipe,
			  ktime_t *tvblank, bool in_vblank_irq)
{
	bool ret = false;

	/* Define requested maximum error on timestamps (nanoseconds). */
	int max_error = (int) drm_timestamp_precision * 1000;

	/* Query driver if possible and precision timestamping enabled. */
	if (dev->driver->get_vblank_timestamp && (max_error > 0))
		ret = dev->driver->get_vblank_timestamp(dev, pipe, &max_error,
							tvblank, in_vblank_irq);

	/* GPU high precision timestamp query unsupported or failed.
	 * Return current monotonic/gettimeofday timestamp as best estimate.
	 */
	if (!ret)
		*tvblank = ktime_get();

	return ret;
}