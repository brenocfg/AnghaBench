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
struct qm_portal_config {int /*<<< orphan*/  channel; int /*<<< orphan*/  dev; scalar_t__ iommu_domain; } ;
struct pamu_stash_attribute {unsigned int cpu; int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_ATTR_FSL_PAMU_STASH ; 
 int /*<<< orphan*/  PAMU_ATTR_CACHE_L1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int iommu_domain_set_attr (scalar_t__,int /*<<< orphan*/ ,struct pamu_stash_attribute*) ; 
 int /*<<< orphan*/  qman_set_sdest (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void qman_portal_update_sdest(const struct qm_portal_config *pcfg,
							unsigned int cpu)
{
#ifdef CONFIG_FSL_PAMU /* TODO */
	struct pamu_stash_attribute stash_attr;
	int ret;

	if (pcfg->iommu_domain) {
		stash_attr.cpu = cpu;
		stash_attr.cache = PAMU_ATTR_CACHE_L1;
		ret = iommu_domain_set_attr(pcfg->iommu_domain,
				DOMAIN_ATTR_FSL_PAMU_STASH, &stash_attr);
		if (ret < 0) {
			dev_err(pcfg->dev,
				"Failed to update pamu stash setting\n");
			return;
		}
	}
#endif
	qman_set_sdest(pcfg->channel, cpu);
}