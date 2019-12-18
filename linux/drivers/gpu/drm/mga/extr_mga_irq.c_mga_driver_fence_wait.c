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
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_fence_retired; int /*<<< orphan*/  fence_queue; } ;
typedef  TYPE_1__ drm_mga_private_t ;

/* Variables and functions */
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void mga_driver_fence_wait(struct drm_device *dev, unsigned int *sequence)
{
	drm_mga_private_t *dev_priv = (drm_mga_private_t *) dev->dev_private;
	unsigned int cur_fence;

	/* Assume that the user has missed the current sequence number
	 * by about a day rather than she wants to wait for years
	 * using fences.
	 */
	wait_event_timeout(dev_priv->fence_queue,
		    (((cur_fence = atomic_read(&dev_priv->last_fence_retired))
		      - *sequence) <= (1 << 23)),
		    msecs_to_jiffies(3000));

	*sequence = cur_fence;
}