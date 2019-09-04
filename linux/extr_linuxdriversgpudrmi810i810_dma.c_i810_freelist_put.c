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
struct drm_device {int dummy; } ;
struct drm_buf {int /*<<< orphan*/  idx; TYPE_1__* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  in_use; } ;
typedef  TYPE_1__ drm_i810_buf_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int I810_BUF_CLIENT ; 
 int /*<<< orphan*/  I810_BUF_FREE ; 
 int cmpxchg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i810_freelist_put(struct drm_device *dev, struct drm_buf *buf)
{
	drm_i810_buf_priv_t *buf_priv = buf->dev_private;
	int used;

	/* In use is already a pointer */
	used = cmpxchg(buf_priv->in_use, I810_BUF_CLIENT, I810_BUF_FREE);
	if (used != I810_BUF_CLIENT) {
		DRM_ERROR("Freeing buffer thats not in use : %d\n", buf->idx);
		return -EINVAL;
	}

	return 0;
}