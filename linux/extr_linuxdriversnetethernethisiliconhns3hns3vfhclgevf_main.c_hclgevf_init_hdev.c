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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hclgevf_dev {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_DRIVER_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int hclgevf_alloc_tqps (struct hclgevf_dev*) ; 
 int hclgevf_cfg_func_mta_type (struct hclgevf_dev*) ; 
 int hclgevf_cmd_init (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_cmd_uninit (struct hclgevf_dev*) ; 
 int hclgevf_configure (struct hclgevf_dev*) ; 
 scalar_t__ hclgevf_dev_ongoing_full_reset (struct hclgevf_dev*) ; 
 int hclgevf_init_msi (struct hclgevf_dev*) ; 
 int hclgevf_init_vlan_config (struct hclgevf_dev*) ; 
 int hclgevf_misc_irq_init (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_misc_irq_uninit (struct hclgevf_dev*) ; 
 int hclgevf_pci_init (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_pci_uninit (struct hclgevf_dev*) ; 
 int hclgevf_query_vf_resource (struct hclgevf_dev*) ; 
 int hclgevf_rss_init_hw (struct hclgevf_dev*) ; 
 int hclgevf_set_handle_info (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_state_init (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_state_uninit (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_uninit_hdev (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_uninit_msi (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_init_hdev(struct hclgevf_dev *hdev)
{
	struct pci_dev *pdev = hdev->pdev;
	int ret;

	/* check if device is on-going full reset(i.e. pcie as well) */
	if (hclgevf_dev_ongoing_full_reset(hdev)) {
		dev_warn(&pdev->dev, "device is going full reset\n");
		hclgevf_uninit_hdev(hdev);
	}

	ret = hclgevf_pci_init(hdev);
	if (ret) {
		dev_err(&pdev->dev, "PCI initialization failed\n");
		return ret;
	}

	ret = hclgevf_cmd_init(hdev);
	if (ret)
		goto err_cmd_init;

	/* Get vf resource */
	ret = hclgevf_query_vf_resource(hdev);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Query vf status error, ret = %d.\n", ret);
		goto err_query_vf;
	}

	ret = hclgevf_init_msi(hdev);
	if (ret) {
		dev_err(&pdev->dev, "failed(%d) to init MSI/MSI-X\n", ret);
		goto err_query_vf;
	}

	hclgevf_state_init(hdev);

	ret = hclgevf_misc_irq_init(hdev);
	if (ret) {
		dev_err(&pdev->dev, "failed(%d) to init Misc IRQ(vector0)\n",
			ret);
		goto err_misc_irq_init;
	}

	ret = hclgevf_configure(hdev);
	if (ret) {
		dev_err(&pdev->dev, "failed(%d) to fetch configuration\n", ret);
		goto err_config;
	}

	ret = hclgevf_alloc_tqps(hdev);
	if (ret) {
		dev_err(&pdev->dev, "failed(%d) to allocate TQPs\n", ret);
		goto err_config;
	}

	ret = hclgevf_set_handle_info(hdev);
	if (ret) {
		dev_err(&pdev->dev, "failed(%d) to set handle info\n", ret);
		goto err_config;
	}

	/* Initialize mta type for this VF */
	ret = hclgevf_cfg_func_mta_type(hdev);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"failed(%d) to initialize MTA type\n", ret);
		goto err_config;
	}

	/* Initialize RSS for this VF */
	ret = hclgevf_rss_init_hw(hdev);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"failed(%d) to initialize RSS\n", ret);
		goto err_config;
	}

	ret = hclgevf_init_vlan_config(hdev);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"failed(%d) to initialize VLAN config\n", ret);
		goto err_config;
	}

	pr_info("finished initializing %s driver\n", HCLGEVF_DRIVER_NAME);

	return 0;

err_config:
	hclgevf_misc_irq_uninit(hdev);
err_misc_irq_init:
	hclgevf_state_uninit(hdev);
	hclgevf_uninit_msi(hdev);
err_query_vf:
	hclgevf_cmd_uninit(hdev);
err_cmd_init:
	hclgevf_pci_uninit(hdev);
	return ret;
}