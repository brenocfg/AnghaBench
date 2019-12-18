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
struct pci_dev {int dummy; } ;
struct nvmet_ns {int /*<<< orphan*/  nsid; int /*<<< orphan*/  device_path; scalar_t__ p2p_dev; int /*<<< orphan*/  use_p2pmem; } ;
struct nvmet_ctrl {int /*<<< orphan*/  p2p_ns_map; struct device* p2p_client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct device**) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct device* nvmet_ns_dev (struct nvmet_ns*) ; 
 struct pci_dev* pci_dev_get (scalar_t__) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int pci_p2pdma_distance (scalar_t__,struct device*,int) ; 
 struct pci_dev* pci_p2pmem_find_many (struct device**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pci_dev*) ; 

__attribute__((used)) static void nvmet_p2pmem_ns_add_p2p(struct nvmet_ctrl *ctrl,
				    struct nvmet_ns *ns)
{
	struct device *clients[2];
	struct pci_dev *p2p_dev;
	int ret;

	if (!ctrl->p2p_client || !ns->use_p2pmem)
		return;

	if (ns->p2p_dev) {
		ret = pci_p2pdma_distance(ns->p2p_dev, ctrl->p2p_client, true);
		if (ret < 0)
			return;

		p2p_dev = pci_dev_get(ns->p2p_dev);
	} else {
		clients[0] = ctrl->p2p_client;
		clients[1] = nvmet_ns_dev(ns);

		p2p_dev = pci_p2pmem_find_many(clients, ARRAY_SIZE(clients));
		if (!p2p_dev) {
			pr_err("no peer-to-peer memory is available that's supported by %s and %s\n",
			       dev_name(ctrl->p2p_client), ns->device_path);
			return;
		}
	}

	ret = radix_tree_insert(&ctrl->p2p_ns_map, ns->nsid, p2p_dev);
	if (ret < 0)
		pci_dev_put(p2p_dev);

	pr_info("using p2pmem on %s for nsid %d\n", pci_name(p2p_dev),
		ns->nsid);
}