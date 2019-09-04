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
struct etnaviv_vram_mapping {int dummy; } ;
struct etnaviv_gem_submit {int nr_bos; TYPE_1__* bos; int /*<<< orphan*/  gpu; } ;
struct etnaviv_gem_object {int /*<<< orphan*/  gpu_active; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {struct etnaviv_vram_mapping* mapping; int /*<<< orphan*/  flags; struct etnaviv_gem_object* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_PINNED ; 
 scalar_t__ IS_ERR (struct etnaviv_vram_mapping*) ; 
 int PTR_ERR (struct etnaviv_vram_mapping*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct etnaviv_vram_mapping* etnaviv_gem_mapping_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int submit_pin_objects(struct etnaviv_gem_submit *submit)
{
	int i, ret = 0;

	for (i = 0; i < submit->nr_bos; i++) {
		struct etnaviv_gem_object *etnaviv_obj = submit->bos[i].obj;
		struct etnaviv_vram_mapping *mapping;

		mapping = etnaviv_gem_mapping_get(&etnaviv_obj->base,
						  submit->gpu);
		if (IS_ERR(mapping)) {
			ret = PTR_ERR(mapping);
			break;
		}
		atomic_inc(&etnaviv_obj->gpu_active);

		submit->bos[i].flags |= BO_PINNED;
		submit->bos[i].mapping = mapping;
	}

	return ret;
}