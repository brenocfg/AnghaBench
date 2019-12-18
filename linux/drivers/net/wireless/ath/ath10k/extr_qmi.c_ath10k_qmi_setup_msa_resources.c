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
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct ath10k_qmi {int /*<<< orphan*/  msa_va; int /*<<< orphan*/  msa_pa; int /*<<< orphan*/  msa_mem_size; struct ath10k* ar; } ;
struct ath10k {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_QMI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMREMAP_WT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_memremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int ath10k_qmi_setup_msa_resources(struct ath10k_qmi *qmi, u32 msa_size)
{
	struct ath10k *ar = qmi->ar;
	struct device *dev = ar->dev;
	struct device_node *node;
	struct resource r;
	int ret;

	node = of_parse_phandle(dev->of_node, "memory-region", 0);
	if (node) {
		ret = of_address_to_resource(node, 0, &r);
		if (ret) {
			dev_err(dev, "failed to resolve msa fixed region\n");
			return ret;
		}
		of_node_put(node);

		qmi->msa_pa = r.start;
		qmi->msa_mem_size = resource_size(&r);
		qmi->msa_va = devm_memremap(dev, qmi->msa_pa, qmi->msa_mem_size,
					    MEMREMAP_WT);
		if (IS_ERR(qmi->msa_va)) {
			dev_err(dev, "failed to map memory region: %pa\n", &r.start);
			return PTR_ERR(qmi->msa_va);
		}
	} else {
		qmi->msa_va = dmam_alloc_coherent(dev, msa_size,
						  &qmi->msa_pa, GFP_KERNEL);
		if (!qmi->msa_va) {
			ath10k_err(ar, "failed to allocate dma memory for msa region\n");
			return -ENOMEM;
		}
		qmi->msa_mem_size = msa_size;
	}

	ath10k_dbg(ar, ATH10K_DBG_QMI, "msa pa: %pad , msa va: 0x%p\n",
		   &qmi->msa_pa,
		   qmi->msa_va);

	return 0;
}