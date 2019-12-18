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
typedef  int u64 ;
typedef  int u32 ;
struct panfrost_model {char* name; int features; int issues; TYPE_1__* revs; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int shader_present; int tiler_present; int l2_present; int stack_present; int revision; int id; int hw_features; int hw_issues; void* js_present; void* as_present; void* mmu_features; void* mem_features; void* tiler_features; void* core_features; void* l2_features; void* thread_tls_alloc; int /*<<< orphan*/  nr_core_groups; void** js_features; void** texture_features; void* coherency_features; void* thread_max_barrier_sz; void* thread_max_workgroup_sz; void* max_threads; void* thread_features; } ;
struct panfrost_device {TYPE_2__ features; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int revision; int issues; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPU_AS_PRESENT ; 
 int /*<<< orphan*/  GPU_COHERENCY_FEATURES ; 
 int /*<<< orphan*/  GPU_CORE_FEATURES ; 
 int /*<<< orphan*/  GPU_ID ; 
 int /*<<< orphan*/  GPU_JS_FEATURES (int) ; 
 int /*<<< orphan*/  GPU_JS_PRESENT ; 
 int /*<<< orphan*/  GPU_L2_FEATURES ; 
 int /*<<< orphan*/  GPU_L2_PRESENT_HI ; 
 int /*<<< orphan*/  GPU_L2_PRESENT_LO ; 
 int /*<<< orphan*/  GPU_MEM_FEATURES ; 
 int /*<<< orphan*/  GPU_MMU_FEATURES ; 
 int /*<<< orphan*/  GPU_SHADER_PRESENT_HI ; 
 int /*<<< orphan*/  GPU_SHADER_PRESENT_LO ; 
 int /*<<< orphan*/  GPU_STACK_PRESENT_HI ; 
 int /*<<< orphan*/  GPU_STACK_PRESENT_LO ; 
 int /*<<< orphan*/  GPU_TEXTURE_FEATURES (int) ; 
 int /*<<< orphan*/  GPU_THREAD_FEATURES ; 
 int /*<<< orphan*/  GPU_THREAD_MAX_BARRIER_SIZE ; 
 int /*<<< orphan*/  GPU_THREAD_MAX_THREADS ; 
 int /*<<< orphan*/  GPU_THREAD_MAX_WORKGROUP_SIZE ; 
 int /*<<< orphan*/  GPU_THREAD_TLS_ALLOC ; 
 int /*<<< orphan*/  GPU_TILER_FEATURES ; 
 int /*<<< orphan*/  GPU_TILER_PRESENT_HI ; 
 int /*<<< orphan*/  GPU_TILER_PRESENT_LO ; 
 int MAX_HW_REVS ; 
 int /*<<< orphan*/  bitmap_from_u64 (int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 struct panfrost_model* gpu_models ; 
 void* gpu_read (struct panfrost_device*,int /*<<< orphan*/ ) ; 
 int hw_issues_all ; 
 int hweight32 (void*) ; 
 int /*<<< orphan*/  hweight64 (int) ; 
 int /*<<< orphan*/  panfrost_model_eq (struct panfrost_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void panfrost_gpu_init_features(struct panfrost_device *pfdev)
{
	u32 gpu_id, num_js, major, minor, status, rev;
	const char *name = "unknown";
	u64 hw_feat = 0;
	u64 hw_issues = hw_issues_all;
	const struct panfrost_model *model;
	int i;

	pfdev->features.l2_features = gpu_read(pfdev, GPU_L2_FEATURES);
	pfdev->features.core_features = gpu_read(pfdev, GPU_CORE_FEATURES);
	pfdev->features.tiler_features = gpu_read(pfdev, GPU_TILER_FEATURES);
	pfdev->features.mem_features = gpu_read(pfdev, GPU_MEM_FEATURES);
	pfdev->features.mmu_features = gpu_read(pfdev, GPU_MMU_FEATURES);
	pfdev->features.thread_features = gpu_read(pfdev, GPU_THREAD_FEATURES);
	pfdev->features.max_threads = gpu_read(pfdev, GPU_THREAD_MAX_THREADS);
	pfdev->features.thread_max_workgroup_sz = gpu_read(pfdev, GPU_THREAD_MAX_WORKGROUP_SIZE);
	pfdev->features.thread_max_barrier_sz = gpu_read(pfdev, GPU_THREAD_MAX_BARRIER_SIZE);
	pfdev->features.coherency_features = gpu_read(pfdev, GPU_COHERENCY_FEATURES);
	for (i = 0; i < 4; i++)
		pfdev->features.texture_features[i] = gpu_read(pfdev, GPU_TEXTURE_FEATURES(i));

	pfdev->features.as_present = gpu_read(pfdev, GPU_AS_PRESENT);

	pfdev->features.js_present = gpu_read(pfdev, GPU_JS_PRESENT);
	num_js = hweight32(pfdev->features.js_present);
	for (i = 0; i < num_js; i++)
		pfdev->features.js_features[i] = gpu_read(pfdev, GPU_JS_FEATURES(i));

	pfdev->features.shader_present = gpu_read(pfdev, GPU_SHADER_PRESENT_LO);
	pfdev->features.shader_present |= (u64)gpu_read(pfdev, GPU_SHADER_PRESENT_HI) << 32;

	pfdev->features.tiler_present = gpu_read(pfdev, GPU_TILER_PRESENT_LO);
	pfdev->features.tiler_present |= (u64)gpu_read(pfdev, GPU_TILER_PRESENT_HI) << 32;

	pfdev->features.l2_present = gpu_read(pfdev, GPU_L2_PRESENT_LO);
	pfdev->features.l2_present |= (u64)gpu_read(pfdev, GPU_L2_PRESENT_HI) << 32;
	pfdev->features.nr_core_groups = hweight64(pfdev->features.l2_present);

	pfdev->features.stack_present = gpu_read(pfdev, GPU_STACK_PRESENT_LO);
	pfdev->features.stack_present |= (u64)gpu_read(pfdev, GPU_STACK_PRESENT_HI) << 32;

	pfdev->features.thread_tls_alloc = gpu_read(pfdev, GPU_THREAD_TLS_ALLOC);

	gpu_id = gpu_read(pfdev, GPU_ID);
	pfdev->features.revision = gpu_id & 0xffff;
	pfdev->features.id = gpu_id >> 16;

	/* The T60x has an oddball ID value. Fix it up to the standard Midgard
	 * format so we (and userspace) don't have to special case it.
	 */
	if (pfdev->features.id == 0x6956)
		pfdev->features.id = 0x0600;

	major = (pfdev->features.revision >> 12) & 0xf;
	minor = (pfdev->features.revision >> 4) & 0xff;
	status = pfdev->features.revision & 0xf;
	rev = pfdev->features.revision;

	gpu_id = pfdev->features.id;

	for (model = gpu_models; model->name; model++) {
		int best = -1;

		if (!panfrost_model_eq(pfdev, model->id))
			continue;

		name = model->name;
		hw_feat = model->features;
		hw_issues |= model->issues;
		for (i = 0; i < MAX_HW_REVS; i++) {
			if (model->revs[i].revision == rev) {
				best = i;
				break;
			} else if (model->revs[i].revision == (rev & ~0xf))
				best = i;
		}

		if (best >= 0)
			hw_issues |= model->revs[best].issues;

		break;
	}

	bitmap_from_u64(pfdev->features.hw_features, hw_feat);
	bitmap_from_u64(pfdev->features.hw_issues, hw_issues);

	dev_info(pfdev->dev, "mali-%s id 0x%x major 0x%x minor 0x%x status 0x%x",
		 name, gpu_id, major, minor, status);
	dev_info(pfdev->dev, "features: %64pb, issues: %64pb",
		 pfdev->features.hw_features,
		 pfdev->features.hw_issues);

	dev_info(pfdev->dev, "Features: L2:0x%08x Shader:0x%08x Tiler:0x%08x Mem:0x%0x MMU:0x%08x AS:0x%x JS:0x%x",
		 pfdev->features.l2_features,
		 pfdev->features.core_features,
		 pfdev->features.tiler_features,
		 pfdev->features.mem_features,
		 pfdev->features.mmu_features,
		 pfdev->features.as_present,
		 pfdev->features.js_present);

	dev_info(pfdev->dev, "shader_present=0x%0llx l2_present=0x%0llx",
		 pfdev->features.shader_present, pfdev->features.l2_present);
}