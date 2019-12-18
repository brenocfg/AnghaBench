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
struct of_phandle_args {scalar_t__* args; } ;
struct msm_iommu_dev {int /*<<< orphan*/  ctx_list; } ;
struct msm_iommu_ctx_dev {int num_mids; scalar_t__* mids; int /*<<< orphan*/  list; int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {struct msm_iommu_ctx_dev* iommu; } ;
struct device {TYPE_1__ archdata; int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct msm_iommu_ctx_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void insert_iommu_master(struct device *dev,
				struct msm_iommu_dev **iommu,
				struct of_phandle_args *spec)
{
	struct msm_iommu_ctx_dev *master = dev->archdata.iommu;
	int sid;

	if (list_empty(&(*iommu)->ctx_list)) {
		master = kzalloc(sizeof(*master), GFP_ATOMIC);
		master->of_node = dev->of_node;
		list_add(&master->list, &(*iommu)->ctx_list);
		dev->archdata.iommu = master;
	}

	for (sid = 0; sid < master->num_mids; sid++)
		if (master->mids[sid] == spec->args[0]) {
			dev_warn(dev, "Stream ID 0x%hx repeated; ignoring\n",
				 sid);
			return;
		}

	master->mids[master->num_mids++] = spec->args[0];
}