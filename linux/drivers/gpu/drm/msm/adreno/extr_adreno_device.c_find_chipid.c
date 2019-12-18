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
typedef  int u32 ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct adreno_rev {unsigned int core; unsigned int major; unsigned int minor; unsigned int patchid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int of_property_read_string_index (struct device_node*,char*,int /*<<< orphan*/ ,char const**) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int find_chipid(struct device *dev, struct adreno_rev *rev)
{
	struct device_node *node = dev->of_node;
	const char *compat;
	int ret;
	u32 chipid;

	/* first search the compat strings for qcom,adreno-XYZ.W: */
	ret = of_property_read_string_index(node, "compatible", 0, &compat);
	if (ret == 0) {
		unsigned int r, patch;

		if (sscanf(compat, "qcom,adreno-%u.%u", &r, &patch) == 2 ||
		    sscanf(compat, "amd,imageon-%u.%u", &r, &patch) == 2) {
			rev->core = r / 100;
			r %= 100;
			rev->major = r / 10;
			r %= 10;
			rev->minor = r;
			rev->patchid = patch;

			return 0;
		}
	}

	/* and if that fails, fall back to legacy "qcom,chipid" property: */
	ret = of_property_read_u32(node, "qcom,chipid", &chipid);
	if (ret) {
		DRM_DEV_ERROR(dev, "could not parse qcom,chipid: %d\n", ret);
		return ret;
	}

	rev->core = (chipid >> 24) & 0xff;
	rev->major = (chipid >> 16) & 0xff;
	rev->minor = (chipid >> 8) & 0xff;
	rev->patchid = (chipid & 0xff);

	dev_warn(dev, "Using legacy qcom,chipid binding!\n");
	dev_warn(dev, "Use compatible qcom,adreno-%u%u%u.%u instead.\n",
		rev->core, rev->major, rev->minor, rev->patchid);

	return 0;
}