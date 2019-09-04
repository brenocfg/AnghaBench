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
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {int func; } ;
typedef  TYPE_1__ drm_r128_init_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
#define  R128_CLEANUP_CCE 129 
#define  R128_INIT_CCE 128 
 int r128_do_cleanup_cce (struct drm_device*) ; 
 int r128_do_init_cce (struct drm_device*,TYPE_1__*) ; 

int r128_cce_init(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_r128_init_t *init = data;

	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	switch (init->func) {
	case R128_INIT_CCE:
		return r128_do_init_cce(dev, init);
	case R128_CLEANUP_CCE:
		return r128_do_cleanup_cce(dev);
	}

	return -EINVAL;
}