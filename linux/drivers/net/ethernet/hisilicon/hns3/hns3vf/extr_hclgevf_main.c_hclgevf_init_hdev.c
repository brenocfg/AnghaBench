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
struct pci_dev {int revision; int /*<<< orphan*/  dev; } ;
struct hclgevf_dev {int /*<<< orphan*/  state; struct pci_dev* pdev; int /*<<< orphan*/  last_reset_time; int /*<<< orphan*/  reset_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_DRIVER_NAME ; 
 int /*<<< orphan*/  HCLGEVF_STATE_IRQ_INITED ; 
 int /*<<< orphan*/  HNAE3_VF_FUNC_RESET ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int hclgevf_alloc_tqps (struct hclgevf_dev*) ; 
 int hclgevf_cmd_init (struct hclgevf_dev*) ; 
 int hclgevf_cmd_queue_init (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_cmd_uninit (struct hclgevf_dev*) ; 
 int hclgevf_config_gro (struct hclgevf_dev*,int) ; 
 int hclgevf_configure (struct hclgevf_dev*) ; 
 int hclgevf_init_msi (struct hclgevf_dev*) ; 
 int hclgevf_init_vlan_config (struct hclgevf_dev*) ; 
 int hclgevf_misc_irq_init (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_misc_irq_uninit (struct hclgevf_dev*) ; 
 int hclgevf_pci_init (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_pci_uninit (struct hclgevf_dev*) ; 
 int hclgevf_query_vf_resource (struct hclgevf_dev*) ; 
 int hclgevf_rss_init_hw (struct hclgevf_dev*) ; 
 int hclgevf_set_handle_info (struct hclgevf_dev*) ; 
 int hclgevf_set_promisc_mode (struct hclgevf_dev*,int) ; 
 int /*<<< orphan*/  hclgevf_state_init (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_state_uninit (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_uninit_msi (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclgevf_init_hdev(struct hclgevf_dev *hdev)
{
	struct pci_dev *pdev = hdev->pdev;
	int ret;

	ret = hclgevf_pci_init(hdev);
	if (ret) {
		dev_err(&pdev->dev, "PCI initialization failed\n");
		return ret;
	}

	ret = hclgevf_cmd_queue_init(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Cmd queue init failed: %d\n", ret);
		goto err_cmd_queue_init;
	}

	ret = hclgevf_cmd_init(hdev);
	if (ret)
		goto err_cmd_init;

	/* Get vf resource */
	ret = hclgevf_query_vf_resource(hdev);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Query vf status error, ret = %d.\n", ret);
		goto err_cmd_init;
	}

	ret = hclgevf_init_msi(hdev);
	if (ret) {
		dev_err(&pdev->dev, "failed(%d) to init MSI/MSI-X\n", ret);
		goto err_cmd_init;
	}

	hclgevf_state_init(hdev);
	hdev->reset_level = HNAE3_VF_FUNC_RESET;

	ret = hclgevf_misc_irq_init(hdev);
	if (ret) {
		dev_err(&pdev->dev, "failed(%d) to init Misc IRQ(vector0)\n",
			ret);
		goto err_misc_irq_init;
	}

	set_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state);

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

	ret = hclgevf_config_gro(hdev, true);
	if (ret)
		goto err_config;

	/* vf is not allowed to enable unicast/multicast promisc mode.
	 * For revision 0x20, default to disable broadcast promisc mode,
	 * firmware makes sure broadcast packets can be accepted.
	 * For revision 0x21, default to enable broadcast promisc mode.
	 */
	if (pdev->revision >= 0x21) {
		ret = hclgevf_set_promisc_mode(hdev, true);
		if (ret)
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

	hdev->last_reset_time = jiffies;
	dev_info(&hdev->pdev->dev, "finished initializing %s driver\n",
		 HCLGEVF_DRIVER_NAME);

	return 0;

err_config:
	hclgevf_misc_irq_uninit(hdev);
err_misc_irq_init:
	hclgevf_state_uninit(hdev);
	hclgevf_uninit_msi(hdev);
err_cmd_init:
	hclgevf_cmd_uninit(hdev);
err_cmd_queue_init:
	hclgevf_pci_uninit(hdev);
	clear_bit(HCLGEVF_STATE_IRQ_INITED, &hdev->state);
	return ret;
}