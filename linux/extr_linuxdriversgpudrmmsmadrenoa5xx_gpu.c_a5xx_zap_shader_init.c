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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msm_gpu {struct platform_device* pdev; } ;
struct adreno_gpu {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  zapfw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*) ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int a5xx_zap_shader_resume (struct msm_gpu*) ; 
 int /*<<< orphan*/  qcom_scm_is_available () ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 
 int zap_shader_load_mdt (struct msm_gpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a5xx_zap_shader_init(struct msm_gpu *gpu)
{
	static bool loaded;
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct platform_device *pdev = gpu->pdev;
	int ret;

	/*
	 * If the zap shader is already loaded into memory we just need to kick
	 * the remote processor to reinitialize it
	 */
	if (loaded)
		return a5xx_zap_shader_resume(gpu);

	/* We need SCM to be able to load the firmware */
	if (!qcom_scm_is_available()) {
		DRM_DEV_ERROR(&pdev->dev, "SCM is not available\n");
		return -EPROBE_DEFER;
	}

	/* Each GPU has a target specific zap shader firmware name to use */
	if (!adreno_gpu->info->zapfw) {
		DRM_DEV_ERROR(&pdev->dev,
			"Zap shader firmware file not specified for this target\n");
		return -ENODEV;
	}

	ret = zap_shader_load_mdt(gpu, adreno_gpu->info->zapfw);

	loaded = !ret;

	return ret;
}