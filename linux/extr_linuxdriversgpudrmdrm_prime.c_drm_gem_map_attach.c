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
struct drm_prime_attachment {int /*<<< orphan*/  dir; } ;
struct drm_gem_object {struct drm_device* dev; } ;
struct drm_device {TYPE_1__* driver; } ;
struct dma_buf_attachment {struct drm_prime_attachment* priv; } ;
struct dma_buf {struct drm_gem_object* priv; } ;
struct TYPE_2__ {int (* gem_prime_pin ) (struct drm_gem_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct drm_prime_attachment* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct drm_gem_object*) ; 

int drm_gem_map_attach(struct dma_buf *dma_buf,
		       struct dma_buf_attachment *attach)
{
	struct drm_prime_attachment *prime_attach;
	struct drm_gem_object *obj = dma_buf->priv;
	struct drm_device *dev = obj->dev;

	prime_attach = kzalloc(sizeof(*prime_attach), GFP_KERNEL);
	if (!prime_attach)
		return -ENOMEM;

	prime_attach->dir = DMA_NONE;
	attach->priv = prime_attach;

	if (!dev->driver->gem_prime_pin)
		return 0;

	return dev->driver->gem_prime_pin(obj);
}