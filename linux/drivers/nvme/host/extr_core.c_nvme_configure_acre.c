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
struct nvme_feat_host_behavior {int /*<<< orphan*/  acre; } ;
struct nvme_ctrl {int /*<<< orphan*/ * crdt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVME_ENABLE_ACRE ; 
 int /*<<< orphan*/  NVME_FEAT_HOST_BEHAVIOR ; 
 int /*<<< orphan*/  kfree (struct nvme_feat_host_behavior*) ; 
 struct nvme_feat_host_behavior* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvme_set_features (struct nvme_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvme_feat_host_behavior*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_configure_acre(struct nvme_ctrl *ctrl)
{
	struct nvme_feat_host_behavior *host;
	int ret;

	/* Don't bother enabling the feature if retry delay is not reported */
	if (!ctrl->crdt[0])
		return 0;

	host = kzalloc(sizeof(*host), GFP_KERNEL);
	if (!host)
		return 0;

	host->acre = NVME_ENABLE_ACRE;
	ret = nvme_set_features(ctrl, NVME_FEAT_HOST_BEHAVIOR, 0,
				host, sizeof(*host), NULL);
	kfree(host);
	return ret;
}