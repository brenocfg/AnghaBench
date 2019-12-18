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
struct nvkm_tags {int /*<<< orphan*/  mn; int /*<<< orphan*/  refcount; } ;
struct nvkm_memory {int /*<<< orphan*/ * tags; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct nvkm_fb {TYPE_1__ subdev; int /*<<< orphan*/  tags; } ;
struct nvkm_device {struct nvkm_fb* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_mm_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void
nvkm_memory_tags_put(struct nvkm_memory *memory, struct nvkm_device *device,
		     struct nvkm_tags **ptags)
{
	struct nvkm_fb *fb = device->fb;
	struct nvkm_tags *tags = *ptags;
	if (tags) {
		mutex_lock(&fb->subdev.mutex);
		if (refcount_dec_and_test(&tags->refcount)) {
			nvkm_mm_free(&fb->tags, &tags->mn);
			kfree(memory->tags);
			memory->tags = NULL;
		}
		mutex_unlock(&fb->subdev.mutex);
		*ptags = NULL;
	}
}