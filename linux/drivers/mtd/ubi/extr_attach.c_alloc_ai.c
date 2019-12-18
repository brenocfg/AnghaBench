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
struct ubi_attach_info {int /*<<< orphan*/  aeb_slab_cache; int /*<<< orphan*/  volumes; int /*<<< orphan*/  fastmap; int /*<<< orphan*/  alien; int /*<<< orphan*/  erase; int /*<<< orphan*/  free; int /*<<< orphan*/  corr; } ;
struct ubi_ainf_peb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  kfree (struct ubi_attach_info*) ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ubi_attach_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ubi_attach_info *alloc_ai(void)
{
	struct ubi_attach_info *ai;

	ai = kzalloc(sizeof(struct ubi_attach_info), GFP_KERNEL);
	if (!ai)
		return ai;

	INIT_LIST_HEAD(&ai->corr);
	INIT_LIST_HEAD(&ai->free);
	INIT_LIST_HEAD(&ai->erase);
	INIT_LIST_HEAD(&ai->alien);
	INIT_LIST_HEAD(&ai->fastmap);
	ai->volumes = RB_ROOT;
	ai->aeb_slab_cache = kmem_cache_create("ubi_aeb_slab_cache",
					       sizeof(struct ubi_ainf_peb),
					       0, 0, NULL);
	if (!ai->aeb_slab_cache) {
		kfree(ai);
		ai = NULL;
	}

	return ai;
}