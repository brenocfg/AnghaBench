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
struct panfrost_perfcnt {size_t bosize; int /*<<< orphan*/  lock; int /*<<< orphan*/  dump_comp; } ;
struct TYPE_2__ {int mem_features; int /*<<< orphan*/  shader_present; int /*<<< orphan*/  l2_present; } ;
struct panfrost_device {struct panfrost_perfcnt* perfcnt; int /*<<< orphan*/  dev; TYPE_1__ features; } ;

/* Variables and functions */
 unsigned int BLOCKS_PER_COREGROUP ; 
 unsigned int BYTES_PER_COUNTER ; 
 unsigned int COUNTERS_PER_BLOCK ; 
 int ENOMEM ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPU_PERFCNT_CFG ; 
 int /*<<< orphan*/  GPU_PERFCNT_CFG_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPU_PERFCNT_CFG_MODE_OFF ; 
 int /*<<< orphan*/  GPU_PRFCNT_JM_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_MMU_L2_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_SHADER_EN ; 
 int /*<<< orphan*/  GPU_PRFCNT_TILER_EN ; 
 int /*<<< orphan*/  HW_FEATURE_V4 ; 
 struct panfrost_perfcnt* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned int fls64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct panfrost_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int hweight64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ panfrost_has_hw_feature (struct panfrost_device*,int /*<<< orphan*/ ) ; 

int panfrost_perfcnt_init(struct panfrost_device *pfdev)
{
	struct panfrost_perfcnt *perfcnt;
	size_t size;

	if (panfrost_has_hw_feature(pfdev, HW_FEATURE_V4)) {
		unsigned int ncoregroups;

		ncoregroups = hweight64(pfdev->features.l2_present);
		size = ncoregroups * BLOCKS_PER_COREGROUP *
		       COUNTERS_PER_BLOCK * BYTES_PER_COUNTER;
	} else {
		unsigned int nl2c, ncores;

		/*
		 * TODO: define a macro to extract the number of l2 caches from
		 * mem_features.
		 */
		nl2c = ((pfdev->features.mem_features >> 8) & GENMASK(3, 0)) + 1;

		/*
		 * shader_present might be sparse, but the counters layout
		 * forces to dump unused regions too, hence the fls64() call
		 * instead of hweight64().
		 */
		ncores = fls64(pfdev->features.shader_present);

		/*
		 * There's always one JM and one Tiler block, hence the '+ 2'
		 * here.
		 */
		size = (nl2c + ncores + 2) *
		       COUNTERS_PER_BLOCK * BYTES_PER_COUNTER;
	}

	perfcnt = devm_kzalloc(pfdev->dev, sizeof(*perfcnt), GFP_KERNEL);
	if (!perfcnt)
		return -ENOMEM;

	perfcnt->bosize = size;

	/* Start with everything disabled. */
	gpu_write(pfdev, GPU_PERFCNT_CFG,
		  GPU_PERFCNT_CFG_MODE(GPU_PERFCNT_CFG_MODE_OFF));
	gpu_write(pfdev, GPU_PRFCNT_JM_EN, 0);
	gpu_write(pfdev, GPU_PRFCNT_SHADER_EN, 0);
	gpu_write(pfdev, GPU_PRFCNT_MMU_L2_EN, 0);
	gpu_write(pfdev, GPU_PRFCNT_TILER_EN, 0);

	init_completion(&perfcnt->dump_comp);
	mutex_init(&perfcnt->lock);
	pfdev->perfcnt = perfcnt;

	return 0;
}