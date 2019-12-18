#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hnae3_ae_dev {scalar_t__ hw_err_reset_req; struct hclge_dev* priv; struct pci_dev* pdev; } ;
struct TYPE_3__ {scalar_t__ media_type; int /*<<< orphan*/  mdio_bus; scalar_t__ phydev; } ;
struct TYPE_4__ {int /*<<< orphan*/  io_base; TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; struct pci_dev* pdev; scalar_t__ last_reset_time; int /*<<< orphan*/  misc_vector; int /*<<< orphan*/  reset_timer; int /*<<< orphan*/  mbx_service_task; int /*<<< orphan*/  rst_service_task; int /*<<< orphan*/  service_task; int /*<<< orphan*/  mac_tnl_log; int /*<<< orphan*/  fd_rule_lock; int /*<<< orphan*/  vport_cfg_mutex; int /*<<< orphan*/  vport_lock; scalar_t__ mps; int /*<<< orphan*/  reset_level; int /*<<< orphan*/  reset_type; struct hnae3_ae_dev* ae_dev; } ;
typedef  enum hnae3_reset_type { ____Placeholder_hnae3_reset_type } hnae3_reset_type ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ ETH_FRAME_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCLGE_DRIVER_NAME ; 
 scalar_t__ HCLGE_RESET_INTERVAL ; 
 int /*<<< orphan*/  HCLGE_TSO_MSS_MAX ; 
 int /*<<< orphan*/  HCLGE_TSO_MSS_MIN ; 
 int /*<<< orphan*/  HNAE3_FUNC_RESET ; 
 scalar_t__ HNAE3_MEDIA_TYPE_COPPER ; 
 int /*<<< orphan*/  HNAE3_NONE_RESET ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_KFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct hclge_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int hclge_alloc_tqps (struct hclge_dev*) ; 
 int hclge_alloc_vport (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_clear_all_event_cause (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_clear_resetting_state (struct hclge_dev*) ; 
 int hclge_cmd_init (struct hclge_dev*) ; 
 int hclge_cmd_queue_init (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_cmd_uninit (struct hclge_dev*) ; 
 int hclge_config_gro (struct hclge_dev*,int) ; 
 int hclge_config_tso (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hclge_configure (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_dcb_ops_set (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_enable_vector (int /*<<< orphan*/ *,int) ; 
 int hclge_get_cap (struct hclge_dev*) ; 
 int hclge_get_reset_level (struct hnae3_ae_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  hclge_handle_all_hns_hw_errors (struct hnae3_ae_dev*) ; 
 int hclge_init_fd_config (struct hclge_dev*) ; 
 int hclge_init_msi (struct hclge_dev*) ; 
 int hclge_init_umv_space (struct hclge_dev*) ; 
 int hclge_init_vlan_config (struct hclge_dev*) ; 
 int hclge_mac_init (struct hclge_dev*) ; 
 int hclge_mac_mdio_config (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_mailbox_service_task ; 
 int hclge_map_tqp (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_misc_affinity_setup (struct hclge_dev*) ; 
 int hclge_misc_irq_init (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_misc_irq_uninit (struct hclge_dev*) ; 
 int hclge_pci_init (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_reset_service_task ; 
 int /*<<< orphan*/  hclge_reset_timer ; 
 int /*<<< orphan*/  hclge_rss_init_cfg (struct hclge_dev*) ; 
 int hclge_rss_init_hw (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_service_task ; 
 int /*<<< orphan*/  hclge_set_def_reset_request (struct hnae3_ae_dev*,int) ; 
 int /*<<< orphan*/  hclge_state_init (struct hclge_dev*) ; 
 int hclge_tm_schd_init (struct hclge_dev*) ; 
 int init_mgr_tbl (struct hclge_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pcim_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_init_ae_dev(struct hnae3_ae_dev *ae_dev)
{
	struct pci_dev *pdev = ae_dev->pdev;
	struct hclge_dev *hdev;
	int ret;

	hdev = devm_kzalloc(&pdev->dev, sizeof(*hdev), GFP_KERNEL);
	if (!hdev) {
		ret = -ENOMEM;
		goto out;
	}

	hdev->pdev = pdev;
	hdev->ae_dev = ae_dev;
	hdev->reset_type = HNAE3_NONE_RESET;
	hdev->reset_level = HNAE3_FUNC_RESET;
	ae_dev->priv = hdev;
	hdev->mps = ETH_FRAME_LEN + ETH_FCS_LEN + 2 * VLAN_HLEN;

	mutex_init(&hdev->vport_lock);
	mutex_init(&hdev->vport_cfg_mutex);
	spin_lock_init(&hdev->fd_rule_lock);

	ret = hclge_pci_init(hdev);
	if (ret) {
		dev_err(&pdev->dev, "PCI init failed\n");
		goto out;
	}

	/* Firmware command queue initialize */
	ret = hclge_cmd_queue_init(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Cmd queue init failed, ret = %d.\n", ret);
		goto err_pci_uninit;
	}

	/* Firmware command initialize */
	ret = hclge_cmd_init(hdev);
	if (ret)
		goto err_cmd_uninit;

	ret = hclge_get_cap(hdev);
	if (ret) {
		dev_err(&pdev->dev, "get hw capability error, ret = %d.\n",
			ret);
		goto err_cmd_uninit;
	}

	ret = hclge_configure(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Configure dev error, ret = %d.\n", ret);
		goto err_cmd_uninit;
	}

	ret = hclge_init_msi(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Init MSI/MSI-X error, ret = %d.\n", ret);
		goto err_cmd_uninit;
	}

	ret = hclge_misc_irq_init(hdev);
	if (ret) {
		dev_err(&pdev->dev,
			"Misc IRQ(vector0) init error, ret = %d.\n",
			ret);
		goto err_msi_uninit;
	}

	ret = hclge_alloc_tqps(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Allocate TQPs error, ret = %d.\n", ret);
		goto err_msi_irq_uninit;
	}

	ret = hclge_alloc_vport(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Allocate vport error, ret = %d.\n", ret);
		goto err_msi_irq_uninit;
	}

	ret = hclge_map_tqp(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Map tqp error, ret = %d.\n", ret);
		goto err_msi_irq_uninit;
	}

	if (hdev->hw.mac.media_type == HNAE3_MEDIA_TYPE_COPPER) {
		ret = hclge_mac_mdio_config(hdev);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"mdio config fail ret=%d\n", ret);
			goto err_msi_irq_uninit;
		}
	}

	ret = hclge_init_umv_space(hdev);
	if (ret) {
		dev_err(&pdev->dev, "umv space init error, ret=%d.\n", ret);
		goto err_mdiobus_unreg;
	}

	ret = hclge_mac_init(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Mac init error, ret = %d\n", ret);
		goto err_mdiobus_unreg;
	}

	ret = hclge_config_tso(hdev, HCLGE_TSO_MSS_MIN, HCLGE_TSO_MSS_MAX);
	if (ret) {
		dev_err(&pdev->dev, "Enable tso fail, ret =%d\n", ret);
		goto err_mdiobus_unreg;
	}

	ret = hclge_config_gro(hdev, true);
	if (ret)
		goto err_mdiobus_unreg;

	ret = hclge_init_vlan_config(hdev);
	if (ret) {
		dev_err(&pdev->dev, "VLAN init fail, ret =%d\n", ret);
		goto err_mdiobus_unreg;
	}

	ret = hclge_tm_schd_init(hdev);
	if (ret) {
		dev_err(&pdev->dev, "tm schd init fail, ret =%d\n", ret);
		goto err_mdiobus_unreg;
	}

	hclge_rss_init_cfg(hdev);
	ret = hclge_rss_init_hw(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Rss init fail, ret =%d\n", ret);
		goto err_mdiobus_unreg;
	}

	ret = init_mgr_tbl(hdev);
	if (ret) {
		dev_err(&pdev->dev, "manager table init fail, ret =%d\n", ret);
		goto err_mdiobus_unreg;
	}

	ret = hclge_init_fd_config(hdev);
	if (ret) {
		dev_err(&pdev->dev,
			"fd table init fail, ret=%d\n", ret);
		goto err_mdiobus_unreg;
	}

	INIT_KFIFO(hdev->mac_tnl_log);

	hclge_dcb_ops_set(hdev);

	timer_setup(&hdev->reset_timer, hclge_reset_timer, 0);
	INIT_DELAYED_WORK(&hdev->service_task, hclge_service_task);
	INIT_WORK(&hdev->rst_service_task, hclge_reset_service_task);
	INIT_WORK(&hdev->mbx_service_task, hclge_mailbox_service_task);

	/* Setup affinity after service timer setup because add_timer_on
	 * is called in affinity notify.
	 */
	hclge_misc_affinity_setup(hdev);

	hclge_clear_all_event_cause(hdev);
	hclge_clear_resetting_state(hdev);

	/* Log and clear the hw errors those already occurred */
	hclge_handle_all_hns_hw_errors(ae_dev);

	/* request delayed reset for the error recovery because an immediate
	 * global reset on a PF affecting pending initialization of other PFs
	 */
	if (ae_dev->hw_err_reset_req) {
		enum hnae3_reset_type reset_level;

		reset_level = hclge_get_reset_level(ae_dev,
						    &ae_dev->hw_err_reset_req);
		hclge_set_def_reset_request(ae_dev, reset_level);
		mod_timer(&hdev->reset_timer, jiffies + HCLGE_RESET_INTERVAL);
	}

	/* Enable MISC vector(vector0) */
	hclge_enable_vector(&hdev->misc_vector, true);

	hclge_state_init(hdev);
	hdev->last_reset_time = jiffies;

	dev_info(&hdev->pdev->dev, "%s driver initialization finished.\n",
		 HCLGE_DRIVER_NAME);

	return 0;

err_mdiobus_unreg:
	if (hdev->hw.mac.phydev)
		mdiobus_unregister(hdev->hw.mac.mdio_bus);
err_msi_irq_uninit:
	hclge_misc_irq_uninit(hdev);
err_msi_uninit:
	pci_free_irq_vectors(pdev);
err_cmd_uninit:
	hclge_cmd_uninit(hdev);
err_pci_uninit:
	pcim_iounmap(pdev, hdev->hw.io_base);
	pci_clear_master(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
out:
	return ret;
}