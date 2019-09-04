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
struct TYPE_2__ {int /*<<< orphan*/  platdev; } ;
struct drm_i915_private {TYPE_1__ lpe_audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpe_audio_platdev_destroy(struct drm_i915_private *dev_priv)
{
	/* XXX Note that platform_device_register_full() allocates a dma_mask
	 * and never frees it. We can't free it here as we cannot guarantee
	 * this is the last reference (i.e. that the dma_mask will not be
	 * used after our unregister). So ee choose to leak the sizeof(u64)
	 * allocation here - it should be fixed in the platform_device rather
	 * than us fiddle with its internals.
	 */

	platform_device_unregister(dev_priv->lpe_audio.platdev);
}