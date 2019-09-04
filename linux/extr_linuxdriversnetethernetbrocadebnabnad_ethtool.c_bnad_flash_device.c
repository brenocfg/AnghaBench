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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct firmware {int /*<<< orphan*/  size; scalar_t__ data; } ;
struct ethtool_flash {int /*<<< orphan*/  data; } ;
struct bnad_iocmd_comp {int comp_status; int /*<<< orphan*/  comp; struct bnad* bnad; } ;
struct TYPE_4__ {int /*<<< orphan*/  flash; } ;
struct bnad {int /*<<< orphan*/  bna_lock; int /*<<< orphan*/  id; TYPE_2__ bna; TYPE_1__* pcidev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FLASH_PART_FWIMG ; 
 int BFA_STATUS_OK ; 
 int EIO ; 
 int bfa_nw_flash_update_part (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bnad_iocmd_comp*) ; 
 int /*<<< orphan*/  bnad_cb_completion ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnad_flash_device(struct net_device *netdev, struct ethtool_flash *eflash)
{
	struct bnad *bnad = netdev_priv(netdev);
	struct bnad_iocmd_comp fcomp;
	const struct firmware *fw;
	int ret = 0;

	ret = request_firmware(&fw, eflash->data, &bnad->pcidev->dev);
	if (ret) {
		netdev_err(netdev, "can't load firmware %s\n", eflash->data);
		goto out;
	}

	fcomp.bnad = bnad;
	fcomp.comp_status = 0;

	init_completion(&fcomp.comp);
	spin_lock_irq(&bnad->bna_lock);
	ret = bfa_nw_flash_update_part(&bnad->bna.flash, BFA_FLASH_PART_FWIMG,
				bnad->id, (u8 *)fw->data, fw->size, 0,
				bnad_cb_completion, &fcomp);
	if (ret != BFA_STATUS_OK) {
		netdev_warn(netdev, "flash update failed with err=%d\n", ret);
		ret = -EIO;
		spin_unlock_irq(&bnad->bna_lock);
		goto out;
	}

	spin_unlock_irq(&bnad->bna_lock);
	wait_for_completion(&fcomp.comp);
	if (fcomp.comp_status != BFA_STATUS_OK) {
		ret = -EIO;
		netdev_warn(netdev,
			    "firmware image update failed with err=%d\n",
			    fcomp.comp_status);
	}
out:
	release_firmware(fw);
	return ret;
}