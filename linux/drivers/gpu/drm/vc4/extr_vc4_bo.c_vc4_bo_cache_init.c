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
struct TYPE_3__ {int /*<<< orphan*/  time_timer; int /*<<< orphan*/  time_work; int /*<<< orphan*/  time_list; } ;
struct vc4_dev {int num_labels; TYPE_1__ bo_cache; int /*<<< orphan*/  bo_lock; TYPE_2__* bo_labels; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VC4_BO_TYPE_COUNT ; 
 int /*<<< orphan*/ * bo_type_names ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_bo_cache_time_timer ; 
 int /*<<< orphan*/  vc4_bo_cache_time_work ; 
 int /*<<< orphan*/  vc4_bo_stats_debugfs ; 
 int /*<<< orphan*/  vc4_debugfs_add_file (struct drm_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int vc4_bo_cache_init(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	int i;

	/* Create the initial set of BO labels that the kernel will
	 * use.  This lets us avoid a bunch of string reallocation in
	 * the kernel's draw and BO allocation paths.
	 */
	vc4->bo_labels = kcalloc(VC4_BO_TYPE_COUNT, sizeof(*vc4->bo_labels),
				 GFP_KERNEL);
	if (!vc4->bo_labels)
		return -ENOMEM;
	vc4->num_labels = VC4_BO_TYPE_COUNT;

	BUILD_BUG_ON(ARRAY_SIZE(bo_type_names) != VC4_BO_TYPE_COUNT);
	for (i = 0; i < VC4_BO_TYPE_COUNT; i++)
		vc4->bo_labels[i].name = bo_type_names[i];

	mutex_init(&vc4->bo_lock);

	vc4_debugfs_add_file(dev, "bo_stats", vc4_bo_stats_debugfs, NULL);

	INIT_LIST_HEAD(&vc4->bo_cache.time_list);

	INIT_WORK(&vc4->bo_cache.time_work, vc4_bo_cache_time_work);
	timer_setup(&vc4->bo_cache.time_timer, vc4_bo_cache_time_timer, 0);

	return 0;
}