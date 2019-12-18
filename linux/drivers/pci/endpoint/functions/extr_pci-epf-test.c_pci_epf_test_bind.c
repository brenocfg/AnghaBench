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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct pci_epf_test {int test_reg_bar; TYPE_1__ cmd_handler; struct pci_epc_features const* epc_features; } ;
struct pci_epf_header {int dummy; } ;
struct device {int dummy; } ;
struct pci_epf {int /*<<< orphan*/  msix_interrupts; int /*<<< orphan*/  func_no; int /*<<< orphan*/  msi_interrupts; struct device dev; struct pci_epc* epc; struct pci_epf_header* header; } ;
struct pci_epc_features {int linkup_notifier; int msix_capable; int msi_capable; } ;
struct pci_epc {int dummy; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
 int BAR_0 ; 
 int EINVAL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct pci_epf_test* epf_get_drvdata (struct pci_epf*) ; 
 int /*<<< orphan*/  kpcitest_workqueue ; 
 struct pci_epc_features* pci_epc_get_features (struct pci_epc*,int /*<<< orphan*/ ) ; 
 int pci_epc_get_first_free_bar (struct pci_epc_features const*) ; 
 int pci_epc_set_msi (struct pci_epc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_epc_set_msix (struct pci_epc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_epc_write_header (struct pci_epc*,int /*<<< orphan*/ ,struct pci_epf_header*) ; 
 int /*<<< orphan*/  pci_epf_configure_bar (struct pci_epf*,struct pci_epc_features const*) ; 
 int pci_epf_test_alloc_space (struct pci_epf*) ; 
 int pci_epf_test_set_bar (struct pci_epf*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pci_epf_test_bind(struct pci_epf *epf)
{
	int ret;
	struct pci_epf_test *epf_test = epf_get_drvdata(epf);
	struct pci_epf_header *header = epf->header;
	const struct pci_epc_features *epc_features;
	enum pci_barno test_reg_bar = BAR_0;
	struct pci_epc *epc = epf->epc;
	struct device *dev = &epf->dev;
	bool linkup_notifier = false;
	bool msix_capable = false;
	bool msi_capable = true;

	if (WARN_ON_ONCE(!epc))
		return -EINVAL;

	epc_features = pci_epc_get_features(epc, epf->func_no);
	if (epc_features) {
		linkup_notifier = epc_features->linkup_notifier;
		msix_capable = epc_features->msix_capable;
		msi_capable = epc_features->msi_capable;
		test_reg_bar = pci_epc_get_first_free_bar(epc_features);
		pci_epf_configure_bar(epf, epc_features);
	}

	epf_test->test_reg_bar = test_reg_bar;
	epf_test->epc_features = epc_features;

	ret = pci_epc_write_header(epc, epf->func_no, header);
	if (ret) {
		dev_err(dev, "Configuration header write failed\n");
		return ret;
	}

	ret = pci_epf_test_alloc_space(epf);
	if (ret)
		return ret;

	ret = pci_epf_test_set_bar(epf);
	if (ret)
		return ret;

	if (msi_capable) {
		ret = pci_epc_set_msi(epc, epf->func_no, epf->msi_interrupts);
		if (ret) {
			dev_err(dev, "MSI configuration failed\n");
			return ret;
		}
	}

	if (msix_capable) {
		ret = pci_epc_set_msix(epc, epf->func_no, epf->msix_interrupts);
		if (ret) {
			dev_err(dev, "MSI-X configuration failed\n");
			return ret;
		}
	}

	if (!linkup_notifier)
		queue_work(kpcitest_workqueue, &epf_test->cmd_handler.work);

	return 0;
}