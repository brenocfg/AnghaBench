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
struct pci_dev {int /*<<< orphan*/  untrusted; } ;
struct intel_iommu {int /*<<< orphan*/  lock; int /*<<< orphan*/  segment; int /*<<< orphan*/  ecap; } ;
struct dmar_domain {int /*<<< orphan*/  devices; } ;
struct device_domain_info {int bus; int devfn; int ats_supported; int pasid_supported; int pri_supported; int /*<<< orphan*/  global; int /*<<< orphan*/  link; struct device* dev; struct dmar_domain* domain; int /*<<< orphan*/  auxiliary_domains; scalar_t__ auxd_enabled; int /*<<< orphan*/ * pasid_table; struct intel_iommu* iommu; scalar_t__ ats_qdep; scalar_t__ pri_enabled; scalar_t__ pasid_enabled; scalar_t__ ats_enabled; } ;
struct TYPE_2__ {struct device_domain_info* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PASID_RID2PASID ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ATS ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_PRI ; 
 struct device_domain_info* alloc_devinfo_mem () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  device_domain_list ; 
 int /*<<< orphan*/  device_domain_lock ; 
 scalar_t__ dmar_find_matched_atsr_unit (struct pci_dev*) ; 
 int /*<<< orphan*/  dmar_remove_one_dev_info (struct device*) ; 
 struct device_domain_info* dmar_search_domain_by_dev_info (int /*<<< orphan*/ ,int,int) ; 
 int domain_attach_iommu (struct dmar_domain*,struct intel_iommu*) ; 
 scalar_t__ domain_context_mapping (struct dmar_domain*,struct device*) ; 
 scalar_t__ domain_type_is_si (struct dmar_domain*) ; 
 scalar_t__ ecap_dev_iotlb_support (int /*<<< orphan*/ ) ; 
 scalar_t__ ecap_prs (int /*<<< orphan*/ ) ; 
 struct dmar_domain* find_domain (struct device*) ; 
 int /*<<< orphan*/  free_devinfo_mem (struct device_domain_info*) ; 
 scalar_t__ hw_pass_through ; 
 int intel_pasid_alloc_table (struct device*) ; 
 int intel_pasid_setup_pass_through (struct intel_iommu*,struct dmar_domain*,struct device*,int /*<<< orphan*/ ) ; 
 int intel_pasid_setup_second_level (struct intel_iommu*,struct dmar_domain*,struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pasid_supported (struct intel_iommu*) ; 
 int /*<<< orphan*/  pci_ats_disabled () ; 
 scalar_t__ pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_pasid_features (struct pci_dev*) ; 
 scalar_t__ sm_supported (struct intel_iommu*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static struct dmar_domain *dmar_insert_one_dev_info(struct intel_iommu *iommu,
						    int bus, int devfn,
						    struct device *dev,
						    struct dmar_domain *domain)
{
	struct dmar_domain *found = NULL;
	struct device_domain_info *info;
	unsigned long flags;
	int ret;

	info = alloc_devinfo_mem();
	if (!info)
		return NULL;

	info->bus = bus;
	info->devfn = devfn;
	info->ats_supported = info->pasid_supported = info->pri_supported = 0;
	info->ats_enabled = info->pasid_enabled = info->pri_enabled = 0;
	info->ats_qdep = 0;
	info->dev = dev;
	info->domain = domain;
	info->iommu = iommu;
	info->pasid_table = NULL;
	info->auxd_enabled = 0;
	INIT_LIST_HEAD(&info->auxiliary_domains);

	if (dev && dev_is_pci(dev)) {
		struct pci_dev *pdev = to_pci_dev(info->dev);

		if (!pdev->untrusted &&
		    !pci_ats_disabled() &&
		    ecap_dev_iotlb_support(iommu->ecap) &&
		    pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_ATS) &&
		    dmar_find_matched_atsr_unit(pdev))
			info->ats_supported = 1;

		if (sm_supported(iommu)) {
			if (pasid_supported(iommu)) {
				int features = pci_pasid_features(pdev);
				if (features >= 0)
					info->pasid_supported = features | 1;
			}

			if (info->ats_supported && ecap_prs(iommu->ecap) &&
			    pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_PRI))
				info->pri_supported = 1;
		}
	}

	spin_lock_irqsave(&device_domain_lock, flags);
	if (dev)
		found = find_domain(dev);

	if (!found) {
		struct device_domain_info *info2;
		info2 = dmar_search_domain_by_dev_info(iommu->segment, bus, devfn);
		if (info2) {
			found      = info2->domain;
			info2->dev = dev;
		}
	}

	if (found) {
		spin_unlock_irqrestore(&device_domain_lock, flags);
		free_devinfo_mem(info);
		/* Caller must free the original domain */
		return found;
	}

	spin_lock(&iommu->lock);
	ret = domain_attach_iommu(domain, iommu);
	spin_unlock(&iommu->lock);

	if (ret) {
		spin_unlock_irqrestore(&device_domain_lock, flags);
		free_devinfo_mem(info);
		return NULL;
	}

	list_add(&info->link, &domain->devices);
	list_add(&info->global, &device_domain_list);
	if (dev)
		dev->archdata.iommu = info;
	spin_unlock_irqrestore(&device_domain_lock, flags);

	/* PASID table is mandatory for a PCI device in scalable mode. */
	if (dev && dev_is_pci(dev) && sm_supported(iommu)) {
		ret = intel_pasid_alloc_table(dev);
		if (ret) {
			dev_err(dev, "PASID table allocation failed\n");
			dmar_remove_one_dev_info(dev);
			return NULL;
		}

		/* Setup the PASID entry for requests without PASID: */
		spin_lock(&iommu->lock);
		if (hw_pass_through && domain_type_is_si(domain))
			ret = intel_pasid_setup_pass_through(iommu, domain,
					dev, PASID_RID2PASID);
		else
			ret = intel_pasid_setup_second_level(iommu, domain,
					dev, PASID_RID2PASID);
		spin_unlock(&iommu->lock);
		if (ret) {
			dev_err(dev, "Setup RID2PASID failed\n");
			dmar_remove_one_dev_info(dev);
			return NULL;
		}
	}

	if (dev && domain_context_mapping(domain, dev)) {
		dev_err(dev, "Domain context map failed\n");
		dmar_remove_one_dev_info(dev);
		return NULL;
	}

	return domain;
}