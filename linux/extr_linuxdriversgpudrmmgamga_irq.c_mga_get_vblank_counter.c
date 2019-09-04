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
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  vbl_received; } ;
typedef  TYPE_1__ drm_mga_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

u32 mga_get_vblank_counter(struct drm_device *dev, unsigned int pipe)
{
	const drm_mga_private_t *const dev_priv =
		(drm_mga_private_t *) dev->dev_private;

	if (pipe != 0)
		return 0;

	return atomic_read(&dev_priv->vbl_received);
}