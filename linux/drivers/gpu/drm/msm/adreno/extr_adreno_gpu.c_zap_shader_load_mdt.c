#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct msm_gpu {TYPE_1__* pdev; } ;
struct firmware {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_5__ {scalar_t__ fwloc; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARCH_QCOM ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int E2BIG ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ FW_LOCATION_LEGACY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct firmware const*) ; 
 int /*<<< orphan*/  MEMREMAP_WC ; 
 int PTR_ERR (struct firmware const*) ; 
 struct firmware* adreno_request_fw (TYPE_2__*,char const*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 void* memremap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memunmap (void*) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int qcom_mdt_get_size (struct firmware const*) ; 
 int qcom_mdt_load (struct device*,struct firmware const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int qcom_scm_pas_auth_and_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int resource_size (struct resource*) ; 
 TYPE_2__* to_adreno_gpu (struct msm_gpu*) ; 
 int zap_available ; 

__attribute__((used)) static int zap_shader_load_mdt(struct msm_gpu *gpu, const char *fwname,
		u32 pasid)
{
	struct device *dev = &gpu->pdev->dev;
	const struct firmware *fw;
	struct device_node *np, *mem_np;
	struct resource r;
	phys_addr_t mem_phys;
	ssize_t mem_size;
	void *mem_region = NULL;
	int ret;

	if (!IS_ENABLED(CONFIG_ARCH_QCOM)) {
		zap_available = false;
		return -EINVAL;
	}

	np = of_get_child_by_name(dev->of_node, "zap-shader");
	if (!np) {
		zap_available = false;
		return -ENODEV;
	}

	mem_np = of_parse_phandle(np, "memory-region", 0);
	of_node_put(np);
	if (!mem_np) {
		zap_available = false;
		return -EINVAL;
	}

	ret = of_address_to_resource(mem_np, 0, &r);
	of_node_put(mem_np);
	if (ret)
		return ret;

	mem_phys = r.start;

	/* Request the MDT file for the firmware */
	fw = adreno_request_fw(to_adreno_gpu(gpu), fwname);
	if (IS_ERR(fw)) {
		DRM_DEV_ERROR(dev, "Unable to load %s\n", fwname);
		return PTR_ERR(fw);
	}

	/* Figure out how much memory we need */
	mem_size = qcom_mdt_get_size(fw);
	if (mem_size < 0) {
		ret = mem_size;
		goto out;
	}

	if (mem_size > resource_size(&r)) {
		DRM_DEV_ERROR(dev,
			"memory region is too small to load the MDT\n");
		ret = -E2BIG;
		goto out;
	}

	/* Allocate memory for the firmware image */
	mem_region = memremap(mem_phys, mem_size,  MEMREMAP_WC);
	if (!mem_region) {
		ret = -ENOMEM;
		goto out;
	}

	/*
	 * Load the rest of the MDT
	 *
	 * Note that we could be dealing with two different paths, since
	 * with upstream linux-firmware it would be in a qcom/ subdir..
	 * adreno_request_fw() handles this, but qcom_mdt_load() does
	 * not.  But since we've already gotten through adreno_request_fw()
	 * we know which of the two cases it is:
	 */
	if (to_adreno_gpu(gpu)->fwloc == FW_LOCATION_LEGACY) {
		ret = qcom_mdt_load(dev, fw, fwname, pasid,
				mem_region, mem_phys, mem_size, NULL);
	} else {
		char *newname;

		newname = kasprintf(GFP_KERNEL, "qcom/%s", fwname);

		ret = qcom_mdt_load(dev, fw, newname, pasid,
				mem_region, mem_phys, mem_size, NULL);
		kfree(newname);
	}
	if (ret)
		goto out;

	/* Send the image to the secure world */
	ret = qcom_scm_pas_auth_and_reset(pasid);

	/*
	 * If the scm call returns -EOPNOTSUPP we assume that this target
	 * doesn't need/support the zap shader so quietly fail
	 */
	if (ret == -EOPNOTSUPP)
		zap_available = false;
	else if (ret)
		DRM_DEV_ERROR(dev, "Unable to authorize the image\n");

out:
	if (mem_region)
		memunmap(mem_region);

	release_firmware(fw);

	return ret;
}