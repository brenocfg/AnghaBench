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
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_r128_private_t ;
struct TYPE_2__ {scalar_t__ idle; scalar_t__ flush; } ;
typedef  TYPE_1__ drm_r128_cce_stop_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_INIT_TEST_WITH_RETURN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  r128_do_cce_flush (int /*<<< orphan*/ *) ; 
 int r128_do_cce_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r128_do_cce_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r128_do_engine_reset (struct drm_device*) ; 

int r128_cce_stop(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	drm_r128_cce_stop_t *stop = data;
	int ret;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	/* Flush any pending CCE commands.  This ensures any outstanding
	 * commands are exectuted by the engine before we turn it off.
	 */
	if (stop->flush)
		r128_do_cce_flush(dev_priv);

	/* If we fail to make the engine go idle, we return an error
	 * code so that the DRM ioctl wrapper can try again.
	 */
	if (stop->idle) {
		ret = r128_do_cce_idle(dev_priv);
		if (ret)
			return ret;
	}

	/* Finally, we can turn off the CCE.  If the engine isn't idle,
	 * we will get some dropped triangles as they won't be fully
	 * rendered before the CCE is shut down.
	 */
	r128_do_cce_stop(dev_priv);

	/* Reset the engine */
	r128_do_engine_reset(dev);

	return 0;
}