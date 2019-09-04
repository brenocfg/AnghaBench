#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_gem_object {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 struct drm_gem_object* drm_gem_prime_import_dev (struct drm_device*,struct dma_buf*,int /*<<< orphan*/ ) ; 

struct drm_gem_object *drm_gem_prime_import(struct drm_device *dev,
					    struct dma_buf *dma_buf)
{
	return drm_gem_prime_import_dev(dev, dma_buf, dev->dev);
}