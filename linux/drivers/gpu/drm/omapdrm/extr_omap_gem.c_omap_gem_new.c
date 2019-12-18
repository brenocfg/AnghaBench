#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
union omap_gem_size {int /*<<< orphan*/  bytes; TYPE_1__ tiled; } ;
typedef  int u32 ;
struct drm_gem_object {TYPE_2__* filp; } ;
struct omap_gem_object {int flags; int /*<<< orphan*/  mm_list; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  lock; struct drm_gem_object base; } ;
struct omap_drm_private {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  obj_list; int /*<<< orphan*/  has_dmm; int /*<<< orphan*/  usergart; } ;
struct drm_device {int /*<<< orphan*/  dev; struct omap_drm_private* dev_private; } ;
struct address_space {int dummy; } ;
struct TYPE_4__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GFP_USER ; 
 int OMAP_BO_CACHED ; 
 int OMAP_BO_MEM_DMABUF ; 
 int OMAP_BO_MEM_DMA_API ; 
 int OMAP_BO_MEM_SHMEM ; 
 int OMAP_BO_SCANOUT ; 
 int OMAP_BO_TILED ; 
 int OMAP_BO_UNCACHED ; 
 int OMAP_BO_WC ; 
 size_t PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int __GFP_DMA32 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_alloc_wc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_gem_object_init (struct drm_device*,struct drm_gem_object*,size_t) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_private_object_init (struct drm_device*,struct drm_gem_object*,size_t) ; 
 int /*<<< orphan*/  gem2fmt (int) ; 
 int /*<<< orphan*/  kfree (struct omap_gem_object*) ; 
 struct omap_gem_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (struct address_space*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tiler_align (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tiler_get_cpu_cache_flags () ; 
 size_t tiler_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct drm_gem_object *omap_gem_new(struct drm_device *dev,
		union omap_gem_size gsize, u32 flags)
{
	struct omap_drm_private *priv = dev->dev_private;
	struct omap_gem_object *omap_obj;
	struct drm_gem_object *obj;
	struct address_space *mapping;
	size_t size;
	int ret;

	/* Validate the flags and compute the memory and cache flags. */
	if (flags & OMAP_BO_TILED) {
		if (!priv->usergart) {
			dev_err(dev->dev, "Tiled buffers require DMM\n");
			return NULL;
		}

		/*
		 * Tiled buffers are always shmem paged backed. When they are
		 * scanned out, they are remapped into DMM/TILER.
		 */
		flags &= ~OMAP_BO_SCANOUT;
		flags |= OMAP_BO_MEM_SHMEM;

		/*
		 * Currently don't allow cached buffers. There is some caching
		 * stuff that needs to be handled better.
		 */
		flags &= ~(OMAP_BO_CACHED|OMAP_BO_WC|OMAP_BO_UNCACHED);
		flags |= tiler_get_cpu_cache_flags();
	} else if ((flags & OMAP_BO_SCANOUT) && !priv->has_dmm) {
		/*
		 * OMAP_BO_SCANOUT hints that the buffer doesn't need to be
		 * tiled. However, to lower the pressure on memory allocation,
		 * use contiguous memory only if no TILER is available.
		 */
		flags |= OMAP_BO_MEM_DMA_API;
	} else if (!(flags & OMAP_BO_MEM_DMABUF)) {
		/*
		 * All other buffers not backed by dma_buf are shmem-backed.
		 */
		flags |= OMAP_BO_MEM_SHMEM;
	}

	/* Allocate the initialize the OMAP GEM object. */
	omap_obj = kzalloc(sizeof(*omap_obj), GFP_KERNEL);
	if (!omap_obj)
		return NULL;

	obj = &omap_obj->base;
	omap_obj->flags = flags;
	mutex_init(&omap_obj->lock);

	if (flags & OMAP_BO_TILED) {
		/*
		 * For tiled buffers align dimensions to slot boundaries and
		 * calculate size based on aligned dimensions.
		 */
		tiler_align(gem2fmt(flags), &gsize.tiled.width,
			    &gsize.tiled.height);

		size = tiler_size(gem2fmt(flags), gsize.tiled.width,
				  gsize.tiled.height);

		omap_obj->width = gsize.tiled.width;
		omap_obj->height = gsize.tiled.height;
	} else {
		size = PAGE_ALIGN(gsize.bytes);
	}

	/* Initialize the GEM object. */
	if (!(flags & OMAP_BO_MEM_SHMEM)) {
		drm_gem_private_object_init(dev, obj, size);
	} else {
		ret = drm_gem_object_init(dev, obj, size);
		if (ret)
			goto err_free;

		mapping = obj->filp->f_mapping;
		mapping_set_gfp_mask(mapping, GFP_USER | __GFP_DMA32);
	}

	/* Allocate memory if needed. */
	if (flags & OMAP_BO_MEM_DMA_API) {
		omap_obj->vaddr = dma_alloc_wc(dev->dev, size,
					       &omap_obj->dma_addr,
					       GFP_KERNEL);
		if (!omap_obj->vaddr)
			goto err_release;
	}

	mutex_lock(&priv->list_lock);
	list_add(&omap_obj->mm_list, &priv->obj_list);
	mutex_unlock(&priv->list_lock);

	return obj;

err_release:
	drm_gem_object_release(obj);
err_free:
	kfree(omap_obj);
	return NULL;
}