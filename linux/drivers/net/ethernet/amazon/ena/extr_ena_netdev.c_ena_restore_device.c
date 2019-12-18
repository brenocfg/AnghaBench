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
struct ena_com_dev_get_features_ctx {int dummy; } ;
struct ena_com_dev {int dummy; } ;
struct ena_adapter {int wd_state; int /*<<< orphan*/  flags; int /*<<< orphan*/  timer_service; int /*<<< orphan*/  netdev; scalar_t__ dev_up_before_reset; int /*<<< orphan*/  num_queues; struct pci_dev* pdev; struct ena_com_dev* ena_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_DEVICE_RUNNING ; 
 int /*<<< orphan*/  ENA_FLAG_LINK_UP ; 
 int /*<<< orphan*/  ENA_FLAG_ONGOING_RESET ; 
 int /*<<< orphan*/  ENA_REGS_RESET_DRIVER_INVALID_STATE ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ena_com_abort_admin_commands (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_admin_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_dev_reset (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_mmio_reg_read_request_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_wait_for_abort_completion (struct ena_com_dev*) ; 
 int ena_device_init (struct ena_com_dev*,struct pci_dev*,struct ena_com_dev_get_features_ctx*,int*) ; 
 int ena_device_validate_params (struct ena_adapter*,struct ena_com_dev_get_features_ctx*) ; 
 int /*<<< orphan*/  ena_disable_msix (struct ena_adapter*) ; 
 int ena_enable_msix_and_set_admin_interrupts (struct ena_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_free_mgmnt_irq (struct ena_adapter*) ; 
 int ena_up (struct ena_adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  version ; 

__attribute__((used)) static int ena_restore_device(struct ena_adapter *adapter)
{
	struct ena_com_dev_get_features_ctx get_feat_ctx;
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	struct pci_dev *pdev = adapter->pdev;
	bool wd_state;
	int rc;

	set_bit(ENA_FLAG_ONGOING_RESET, &adapter->flags);
	rc = ena_device_init(ena_dev, adapter->pdev, &get_feat_ctx, &wd_state);
	if (rc) {
		dev_err(&pdev->dev, "Can not initialize device\n");
		goto err;
	}
	adapter->wd_state = wd_state;

	rc = ena_device_validate_params(adapter, &get_feat_ctx);
	if (rc) {
		dev_err(&pdev->dev, "Validation of device parameters failed\n");
		goto err_device_destroy;
	}

	rc = ena_enable_msix_and_set_admin_interrupts(adapter,
						      adapter->num_queues);
	if (rc) {
		dev_err(&pdev->dev, "Enable MSI-X failed\n");
		goto err_device_destroy;
	}
	/* If the interface was up before the reset bring it up */
	if (adapter->dev_up_before_reset) {
		rc = ena_up(adapter);
		if (rc) {
			dev_err(&pdev->dev, "Failed to create I/O queues\n");
			goto err_disable_msix;
		}
	}

	set_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags);

	clear_bit(ENA_FLAG_ONGOING_RESET, &adapter->flags);
	if (test_bit(ENA_FLAG_LINK_UP, &adapter->flags))
		netif_carrier_on(adapter->netdev);

	mod_timer(&adapter->timer_service, round_jiffies(jiffies + HZ));
	dev_err(&pdev->dev,
		"Device reset completed successfully, Driver info: %s\n",
		version);

	return rc;
err_disable_msix:
	ena_free_mgmnt_irq(adapter);
	ena_disable_msix(adapter);
err_device_destroy:
	ena_com_abort_admin_commands(ena_dev);
	ena_com_wait_for_abort_completion(ena_dev);
	ena_com_admin_destroy(ena_dev);
	ena_com_dev_reset(ena_dev, ENA_REGS_RESET_DRIVER_INVALID_STATE);
	ena_com_mmio_reg_read_request_destroy(ena_dev);
err:
	clear_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags);
	clear_bit(ENA_FLAG_ONGOING_RESET, &adapter->flags);
	dev_err(&pdev->dev,
		"Reset attempt failed. Can not reset the device\n");

	return rc;
}