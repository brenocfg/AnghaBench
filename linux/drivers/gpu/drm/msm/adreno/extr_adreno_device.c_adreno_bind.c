#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msm_gpu {int dummy; } ;
struct msm_drm_private {int is_a2xx; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;
struct device {struct adreno_platform_config* platform_data; } ;
struct TYPE_3__ {int core; int /*<<< orphan*/  patchid; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct adreno_platform_config {TYPE_1__ rev; } ;
struct adreno_info {struct msm_gpu* (* init ) (struct drm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 scalar_t__ IS_ERR (struct msm_gpu*) ; 
 int PTR_ERR (struct msm_gpu*) ; 
 struct adreno_info* adreno_info (TYPE_1__) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct msm_gpu*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int find_chipid (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  set_gpu_pdev (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct msm_gpu* stub1 (struct drm_device*) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static int adreno_bind(struct device *dev, struct device *master, void *data)
{
	static struct adreno_platform_config config = {};
	const struct adreno_info *info;
	struct drm_device *drm = dev_get_drvdata(master);
	struct msm_drm_private *priv = drm->dev_private;
	struct msm_gpu *gpu;
	int ret;

	ret = find_chipid(dev, &config.rev);
	if (ret)
		return ret;

	dev->platform_data = &config;
	set_gpu_pdev(drm, to_platform_device(dev));

	info = adreno_info(config.rev);

	if (!info) {
		dev_warn(drm->dev, "Unknown GPU revision: %u.%u.%u.%u\n",
			config.rev.core, config.rev.major,
			config.rev.minor, config.rev.patchid);
		return -ENXIO;
	}

	DBG("Found GPU: %u.%u.%u.%u", config.rev.core, config.rev.major,
		config.rev.minor, config.rev.patchid);

	priv->is_a2xx = config.rev.core == 2;

	gpu = info->init(drm);
	if (IS_ERR(gpu)) {
		dev_warn(drm->dev, "failed to load adreno gpu\n");
		return PTR_ERR(gpu);
	}

	dev_set_drvdata(dev, gpu);

	return 0;
}