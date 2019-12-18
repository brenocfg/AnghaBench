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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct iavf_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct iavf_adapter {scalar_t__ state; TYPE_1__ pf_version; struct iavf_hw hw; struct pci_dev* pdev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int IAVF_ERR_ADMIN_QUEUE_NO_WORK ; 
 int /*<<< orphan*/  VIRTCHNL_VERSION_MAJOR ; 
 int /*<<< orphan*/  VIRTCHNL_VERSION_MINOR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __IAVF_INIT_GET_RESOURCES ; 
 scalar_t__ __IAVF_INIT_VERSION_CHECK ; 
 scalar_t__ __IAVF_STARTUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  iavf_asq_done (struct iavf_hw*) ; 
 int iavf_send_api_ver (struct iavf_adapter*) ; 
 int iavf_send_vf_config_msg (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_shutdown_adminq (struct iavf_hw*) ; 
 int iavf_verify_api_ver (struct iavf_adapter*) ; 

__attribute__((used)) static int iavf_init_version_check(struct iavf_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	struct iavf_hw *hw = &adapter->hw;
	int err = -EAGAIN;

	WARN_ON(adapter->state != __IAVF_INIT_VERSION_CHECK);

	if (!iavf_asq_done(hw)) {
		dev_err(&pdev->dev, "Admin queue command never completed\n");
		iavf_shutdown_adminq(hw);
		adapter->state = __IAVF_STARTUP;
		goto err;
	}

	/* aq msg sent, awaiting reply */
	err = iavf_verify_api_ver(adapter);
	if (err) {
		if (err == IAVF_ERR_ADMIN_QUEUE_NO_WORK)
			err = iavf_send_api_ver(adapter);
		else
			dev_err(&pdev->dev, "Unsupported PF API version %d.%d, expected %d.%d\n",
				adapter->pf_version.major,
				adapter->pf_version.minor,
				VIRTCHNL_VERSION_MAJOR,
				VIRTCHNL_VERSION_MINOR);
		goto err;
	}
	err = iavf_send_vf_config_msg(adapter);
	if (err) {
		dev_err(&pdev->dev, "Unable to send config request (%d)\n",
			err);
		goto err;
	}
	adapter->state = __IAVF_INIT_GET_RESOURCES;

err:
	return err;
}