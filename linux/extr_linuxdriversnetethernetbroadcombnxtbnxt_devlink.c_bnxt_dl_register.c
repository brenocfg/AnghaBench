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
struct devlink {int dummy; } ;
struct bnxt_dl {int dummy; } ;
struct bnxt {int hwrm_spec_code; int /*<<< orphan*/  dev; TYPE_1__* pdev; int /*<<< orphan*/  eswitch_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEVLINK_ESWITCH_MODE_LEGACY ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_SRIOV ; 
 int /*<<< orphan*/  bnxt_dl_ops ; 
 int /*<<< orphan*/  bnxt_dl_params ; 
 int /*<<< orphan*/  bnxt_link_bp_to_dl (struct bnxt*,struct devlink*) ; 
 struct devlink* devlink_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devlink_free (struct devlink*) ; 
 int devlink_params_register (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devlink_register (struct devlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_unregister (struct devlink*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ pci_find_ext_capability (TYPE_1__*,int /*<<< orphan*/ ) ; 

int bnxt_dl_register(struct bnxt *bp)
{
	struct devlink *dl;
	int rc;

	if (bp->hwrm_spec_code < 0x10600) {
		netdev_warn(bp->dev, "Firmware does not support NVM params");
		return -ENOTSUPP;
	}

	dl = devlink_alloc(&bnxt_dl_ops, sizeof(struct bnxt_dl));
	if (!dl) {
		netdev_warn(bp->dev, "devlink_alloc failed");
		return -ENOMEM;
	}

	bnxt_link_bp_to_dl(bp, dl);

	/* Add switchdev eswitch mode setting, if SRIOV supported */
	if (pci_find_ext_capability(bp->pdev, PCI_EXT_CAP_ID_SRIOV) &&
	    bp->hwrm_spec_code > 0x10803)
		bp->eswitch_mode = DEVLINK_ESWITCH_MODE_LEGACY;

	rc = devlink_register(dl, &bp->pdev->dev);
	if (rc) {
		netdev_warn(bp->dev, "devlink_register failed. rc=%d", rc);
		goto err_dl_free;
	}

	rc = devlink_params_register(dl, bnxt_dl_params,
				     ARRAY_SIZE(bnxt_dl_params));
	if (rc) {
		netdev_warn(bp->dev, "devlink_params_register failed. rc=%d",
			    rc);
		goto err_dl_unreg;
	}

	return 0;

err_dl_unreg:
	devlink_unregister(dl);
err_dl_free:
	bnxt_link_bp_to_dl(bp, NULL);
	devlink_free(dl);
	return rc;
}