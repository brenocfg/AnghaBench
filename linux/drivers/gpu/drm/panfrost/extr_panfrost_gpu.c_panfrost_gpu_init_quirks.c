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
typedef  int u32 ;
struct TYPE_2__ {int revision; int coherency_features; } ;
struct panfrost_device {TYPE_1__ features; } ;

/* Variables and functions */
 int COHERENCY_ACE ; 
 int COHERENCY_ACE_LITE ; 
 int /*<<< orphan*/  GPUCORE_1619 ; 
 int /*<<< orphan*/  GPU_JM_CONFIG ; 
 int /*<<< orphan*/  GPU_L2_MMU_CONFIG ; 
 int /*<<< orphan*/  GPU_SHADER_CONFIG ; 
 int /*<<< orphan*/  GPU_TILER_CONFIG ; 
 int /*<<< orphan*/  HW_FEATURE_3BIT_EXT_RW_L2_MMU_CONFIG ; 
 int /*<<< orphan*/  HW_FEATURE_TLS_HASHING ; 
 int /*<<< orphan*/  HW_ISSUE_10327 ; 
 int /*<<< orphan*/  HW_ISSUE_10797 ; 
 int /*<<< orphan*/  HW_ISSUE_11035 ; 
 int /*<<< orphan*/  HW_ISSUE_8443 ; 
 int /*<<< orphan*/  HW_ISSUE_T76X_3953 ; 
 int JM_FORCE_COHERENCY_FEATURES_SHIFT ; 
 int JM_JOB_THROTTLE_LIMIT_SHIFT ; 
 int JM_MAX_JOB_THROTTLE_LIMIT ; 
 int L2_MMU_CONFIG_3BIT_LIMIT_EXTERNAL_READS ; 
 int L2_MMU_CONFIG_3BIT_LIMIT_EXTERNAL_WRITES ; 
 int L2_MMU_CONFIG_LIMIT_EXTERNAL_READS ; 
 int L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES ; 
 int SC_ENABLE_TEXGRD_FLAGS ; 
 int SC_LS_ALLOW_ATTR_TYPES ; 
 int SC_LS_ATTR_CHECK_DISABLE ; 
 int SC_LS_PAUSEBUFFER_DISABLE ; 
 int SC_SDC_DISABLE_OQ_DISCARD ; 
 int SC_TLS_HASH_ENABLE ; 
 int TC_CLOCK_GATE_OVERRIDE ; 
 int gpu_read (struct panfrost_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct panfrost_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ panfrost_has_hw_feature (struct panfrost_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ panfrost_has_hw_issue (struct panfrost_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ panfrost_model_cmp (struct panfrost_device*,int) ; 
 scalar_t__ panfrost_model_eq (struct panfrost_device*,int) ; 

__attribute__((used)) static void panfrost_gpu_init_quirks(struct panfrost_device *pfdev)
{
	u32 quirks = 0;

	if (panfrost_has_hw_issue(pfdev, HW_ISSUE_8443) ||
	    panfrost_has_hw_issue(pfdev, HW_ISSUE_11035))
		quirks |= SC_LS_PAUSEBUFFER_DISABLE;

	if (panfrost_has_hw_issue(pfdev, HW_ISSUE_10327))
		quirks |= SC_SDC_DISABLE_OQ_DISCARD;

	if (panfrost_has_hw_issue(pfdev, HW_ISSUE_10797))
		quirks |= SC_ENABLE_TEXGRD_FLAGS;

	if (!panfrost_has_hw_issue(pfdev, GPUCORE_1619)) {
		if (panfrost_model_cmp(pfdev, 0x750) < 0) /* T60x, T62x, T72x */
			quirks |= SC_LS_ATTR_CHECK_DISABLE;
		else if (panfrost_model_cmp(pfdev, 0x880) <= 0) /* T76x, T8xx */
			quirks |= SC_LS_ALLOW_ATTR_TYPES;
	}

	if (panfrost_has_hw_feature(pfdev, HW_FEATURE_TLS_HASHING))
		quirks |= SC_TLS_HASH_ENABLE;

	if (quirks)
		gpu_write(pfdev, GPU_SHADER_CONFIG, quirks);


	quirks = gpu_read(pfdev, GPU_TILER_CONFIG);

	/* Set tiler clock gate override if required */
	if (panfrost_has_hw_issue(pfdev, HW_ISSUE_T76X_3953))
		quirks |= TC_CLOCK_GATE_OVERRIDE;

	gpu_write(pfdev, GPU_TILER_CONFIG, quirks);


	quirks = gpu_read(pfdev, GPU_L2_MMU_CONFIG);

	/* Limit read & write ID width for AXI */
	if (panfrost_has_hw_feature(pfdev, HW_FEATURE_3BIT_EXT_RW_L2_MMU_CONFIG))
		quirks &= ~(L2_MMU_CONFIG_3BIT_LIMIT_EXTERNAL_READS |
			    L2_MMU_CONFIG_3BIT_LIMIT_EXTERNAL_WRITES);
	else
		quirks &= ~(L2_MMU_CONFIG_LIMIT_EXTERNAL_READS |
			    L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES);

	gpu_write(pfdev, GPU_L2_MMU_CONFIG, quirks);

	quirks = 0;
	if ((panfrost_model_eq(pfdev, 0x860) || panfrost_model_eq(pfdev, 0x880)) &&
	    pfdev->features.revision >= 0x2000)
		quirks |= JM_MAX_JOB_THROTTLE_LIMIT << JM_JOB_THROTTLE_LIMIT_SHIFT;
	else if (panfrost_model_eq(pfdev, 0x6000) &&
		 pfdev->features.coherency_features == COHERENCY_ACE)
		quirks |= (COHERENCY_ACE_LITE | COHERENCY_ACE) <<
			   JM_FORCE_COHERENCY_FEATURES_SHIFT;

	if (quirks)
		gpu_write(pfdev, GPU_JM_CONFIG, quirks);
}