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
struct drm_tile_group {int id; struct drm_device* dev; int /*<<< orphan*/  group_data; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  idr_mutex; int /*<<< orphan*/  tile_idr; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_alloc (int /*<<< orphan*/ *,struct drm_tile_group*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_tile_group*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct drm_tile_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct drm_tile_group *drm_mode_create_tile_group(struct drm_device *dev,
						  char topology[8])
{
	struct drm_tile_group *tg;
	int ret;

	tg = kzalloc(sizeof(*tg), GFP_KERNEL);
	if (!tg)
		return NULL;

	kref_init(&tg->refcount);
	memcpy(tg->group_data, topology, 8);
	tg->dev = dev;

	mutex_lock(&dev->mode_config.idr_mutex);
	ret = idr_alloc(&dev->mode_config.tile_idr, tg, 1, 0, GFP_KERNEL);
	if (ret >= 0) {
		tg->id = ret;
	} else {
		kfree(tg);
		tg = NULL;
	}

	mutex_unlock(&dev->mode_config.idr_mutex);
	return tg;
}