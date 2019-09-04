#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct drm_file {int dummy; } ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_6__ {int /*<<< orphan*/ * virtual_start; } ;
struct TYPE_7__ {TYPE_1__ ring; } ;
typedef  TYPE_2__ drm_via_private_t ;
struct TYPE_8__ {int size; int func; int /*<<< orphan*/  wait; } ;
typedef  TYPE_3__ drm_via_cmdbuf_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EAGAIN ; 
 int EFAULT ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
#define  VIA_CMDBUF_LAG 129 
#define  VIA_CMDBUF_SPACE 128 
 int via_cmdbuf_lag (TYPE_2__*) ; 
 int via_cmdbuf_space (TYPE_2__*) ; 

__attribute__((used)) static int via_cmdbuf_size(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_via_cmdbuf_size_t *d_siz = data;
	int ret = 0;
	uint32_t tmp_size, count;
	drm_via_private_t *dev_priv;

	DRM_DEBUG("\n");
	LOCK_TEST_WITH_RETURN(dev, file_priv);

	dev_priv = (drm_via_private_t *) dev->dev_private;

	if (dev_priv->ring.virtual_start == NULL) {
		DRM_ERROR("called without initializing AGP ring buffer.\n");
		return -EFAULT;
	}

	count = 1000000;
	tmp_size = d_siz->size;
	switch (d_siz->func) {
	case VIA_CMDBUF_SPACE:
		while (((tmp_size = via_cmdbuf_space(dev_priv)) < d_siz->size)
		       && --count) {
			if (!d_siz->wait)
				break;
		}
		if (!count) {
			DRM_ERROR("VIA_CMDBUF_SPACE timed out.\n");
			ret = -EAGAIN;
		}
		break;
	case VIA_CMDBUF_LAG:
		while (((tmp_size = via_cmdbuf_lag(dev_priv)) > d_siz->size)
		       && --count) {
			if (!d_siz->wait)
				break;
		}
		if (!count) {
			DRM_ERROR("VIA_CMDBUF_LAG timed out.\n");
			ret = -EAGAIN;
		}
		break;
	default:
		ret = -EFAULT;
	}
	d_siz->size = tmp_size;

	return ret;
}