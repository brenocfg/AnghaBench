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
struct intel_iommu {void** domain_ids; void** domains; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; int /*<<< orphan*/  cap; } ;
struct dmar_domain {int dummy; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FLPT_DEFAULT_DID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cap_ndoms (int /*<<< orphan*/ ) ; 
 void** kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void**) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ sm_supported (struct intel_iommu*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iommu_init_domains(struct intel_iommu *iommu)
{
	u32 ndomains, nlongs;
	size_t size;

	ndomains = cap_ndoms(iommu->cap);
	pr_debug("%s: Number of Domains supported <%d>\n",
		 iommu->name, ndomains);
	nlongs = BITS_TO_LONGS(ndomains);

	spin_lock_init(&iommu->lock);

	iommu->domain_ids = kcalloc(nlongs, sizeof(unsigned long), GFP_KERNEL);
	if (!iommu->domain_ids) {
		pr_err("%s: Allocating domain id array failed\n",
		       iommu->name);
		return -ENOMEM;
	}

	size = (ALIGN(ndomains, 256) >> 8) * sizeof(struct dmar_domain **);
	iommu->domains = kzalloc(size, GFP_KERNEL);

	if (iommu->domains) {
		size = 256 * sizeof(struct dmar_domain *);
		iommu->domains[0] = kzalloc(size, GFP_KERNEL);
	}

	if (!iommu->domains || !iommu->domains[0]) {
		pr_err("%s: Allocating domain array failed\n",
		       iommu->name);
		kfree(iommu->domain_ids);
		kfree(iommu->domains);
		iommu->domain_ids = NULL;
		iommu->domains    = NULL;
		return -ENOMEM;
	}

	/*
	 * If Caching mode is set, then invalid translations are tagged
	 * with domain-id 0, hence we need to pre-allocate it. We also
	 * use domain-id 0 as a marker for non-allocated domain-id, so
	 * make sure it is not used for a real domain.
	 */
	set_bit(0, iommu->domain_ids);

	/*
	 * Vt-d spec rev3.0 (section 6.2.3.1) requires that each pasid
	 * entry for first-level or pass-through translation modes should
	 * be programmed with a domain id different from those used for
	 * second-level or nested translation. We reserve a domain id for
	 * this purpose.
	 */
	if (sm_supported(iommu))
		set_bit(FLPT_DEFAULT_DID, iommu->domain_ids);

	return 0;
}