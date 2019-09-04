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
struct resources_ispif {int dummy; } ;
struct resources {int dummy; } ;
struct camss {scalar_t__ version; unsigned int csiphy_num; unsigned int csid_num; unsigned int vfe_num; int /*<<< orphan*/  dev; int /*<<< orphan*/ * vfe; int /*<<< orphan*/  ispif; int /*<<< orphan*/ * csid; int /*<<< orphan*/ * csiphy; } ;

/* Variables and functions */
 scalar_t__ CAMSS_8x16 ; 
 scalar_t__ CAMSS_8x96 ; 
 int EINVAL ; 
 struct resources* csid_res_8x16 ; 
 struct resources* csid_res_8x96 ; 
 struct resources* csiphy_res_8x16 ; 
 struct resources* csiphy_res_8x96 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 struct resources_ispif ispif_res_8x16 ; 
 struct resources_ispif ispif_res_8x96 ; 
 int msm_csid_subdev_init (struct camss*,int /*<<< orphan*/ *,struct resources const*,unsigned int) ; 
 int msm_csiphy_subdev_init (struct camss*,int /*<<< orphan*/ *,struct resources const*,unsigned int) ; 
 int msm_ispif_subdev_init (int /*<<< orphan*/ *,struct resources_ispif const*) ; 
 int msm_vfe_subdev_init (struct camss*,int /*<<< orphan*/ *,struct resources const*,unsigned int) ; 
 struct resources* vfe_res_8x16 ; 
 struct resources* vfe_res_8x96 ; 

__attribute__((used)) static int camss_init_subdevices(struct camss *camss)
{
	const struct resources *csiphy_res;
	const struct resources *csid_res;
	const struct resources_ispif *ispif_res;
	const struct resources *vfe_res;
	unsigned int i;
	int ret;

	if (camss->version == CAMSS_8x16) {
		csiphy_res = csiphy_res_8x16;
		csid_res = csid_res_8x16;
		ispif_res = &ispif_res_8x16;
		vfe_res = vfe_res_8x16;
	} else if (camss->version == CAMSS_8x96) {
		csiphy_res = csiphy_res_8x96;
		csid_res = csid_res_8x96;
		ispif_res = &ispif_res_8x96;
		vfe_res = vfe_res_8x96;
	} else {
		return -EINVAL;
	}

	for (i = 0; i < camss->csiphy_num; i++) {
		ret = msm_csiphy_subdev_init(camss, &camss->csiphy[i],
					     &csiphy_res[i], i);
		if (ret < 0) {
			dev_err(camss->dev,
				"Failed to init csiphy%d sub-device: %d\n",
				i, ret);
			return ret;
		}
	}

	for (i = 0; i < camss->csid_num; i++) {
		ret = msm_csid_subdev_init(camss, &camss->csid[i],
					   &csid_res[i], i);
		if (ret < 0) {
			dev_err(camss->dev,
				"Failed to init csid%d sub-device: %d\n",
				i, ret);
			return ret;
		}
	}

	ret = msm_ispif_subdev_init(&camss->ispif, ispif_res);
	if (ret < 0) {
		dev_err(camss->dev, "Failed to init ispif sub-device: %d\n",
			ret);
		return ret;
	}

	for (i = 0; i < camss->vfe_num; i++) {
		ret = msm_vfe_subdev_init(camss, &camss->vfe[i],
					  &vfe_res[i], i);
		if (ret < 0) {
			dev_err(camss->dev,
				"Fail to init vfe%d sub-device: %d\n", i, ret);
			return ret;
		}
	}

	return 0;
}