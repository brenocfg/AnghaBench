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
typedef  int u32 ;
struct etnaviv_gem_ops {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct etnaviv_gem_object {int flags; struct drm_gem_object base; int /*<<< orphan*/  vram_list; int /*<<< orphan*/  lock; struct etnaviv_gem_ops const* ops; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  ETNA_BO_CACHED 130 
 int ETNA_BO_CACHE_MASK ; 
#define  ETNA_BO_UNCACHED 129 
#define  ETNA_BO_WC 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct etnaviv_gem_object* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int etnaviv_gem_new_impl(struct drm_device *dev, u32 size, u32 flags,
	const struct etnaviv_gem_ops *ops, struct drm_gem_object **obj)
{
	struct etnaviv_gem_object *etnaviv_obj;
	unsigned sz = sizeof(*etnaviv_obj);
	bool valid = true;

	/* validate flags */
	switch (flags & ETNA_BO_CACHE_MASK) {
	case ETNA_BO_UNCACHED:
	case ETNA_BO_CACHED:
	case ETNA_BO_WC:
		break;
	default:
		valid = false;
	}

	if (!valid) {
		dev_err(dev->dev, "invalid cache flag: %x\n",
			(flags & ETNA_BO_CACHE_MASK));
		return -EINVAL;
	}

	etnaviv_obj = kzalloc(sz, GFP_KERNEL);
	if (!etnaviv_obj)
		return -ENOMEM;

	etnaviv_obj->flags = flags;
	etnaviv_obj->ops = ops;

	mutex_init(&etnaviv_obj->lock);
	INIT_LIST_HEAD(&etnaviv_obj->vram_list);

	*obj = &etnaviv_obj->base;

	return 0;
}