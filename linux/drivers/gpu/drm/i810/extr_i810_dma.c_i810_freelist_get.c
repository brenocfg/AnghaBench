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
struct drm_device_dma {int buf_count; struct drm_buf** buflist; } ;
struct drm_device {struct drm_device_dma* dma; } ;
struct drm_buf {TYPE_1__* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  in_use; } ;
typedef  TYPE_1__ drm_i810_buf_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  I810_BUF_CLIENT ; 
 int I810_BUF_FREE ; 
 int cmpxchg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_buf *i810_freelist_get(struct drm_device * dev)
{
	struct drm_device_dma *dma = dev->dma;
	int i;
	int used;

	/* Linear search might not be the best solution */

	for (i = 0; i < dma->buf_count; i++) {
		struct drm_buf *buf = dma->buflist[i];
		drm_i810_buf_priv_t *buf_priv = buf->dev_private;
		/* In use is already a pointer */
		used = cmpxchg(buf_priv->in_use, I810_BUF_FREE,
			       I810_BUF_CLIENT);
		if (used == I810_BUF_FREE)
			return buf;
	}
	return NULL;
}