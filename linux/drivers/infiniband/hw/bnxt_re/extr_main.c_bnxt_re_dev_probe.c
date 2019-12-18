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
struct pci_dev {TYPE_2__* driver; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct bnxt_en_dev {int flags; struct pci_dev* pdev; } ;
struct bnxt {struct bnxt_en_dev* (* ulp_probe ) (struct net_device*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct TYPE_4__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int BNXT_EN_FLAG_ROCE_CAP ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct bnxt_en_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct bnxt_en_dev*) ; 
 int /*<<< orphan*/  ROCE_DRV_MODULE_NAME ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 struct bnxt_en_dev* stub1 (struct net_device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bnxt_en_dev *bnxt_re_dev_probe(struct net_device *netdev)
{
	struct bnxt *bp = netdev_priv(netdev);
	struct bnxt_en_dev *en_dev;
	struct pci_dev *pdev;

	/* Call bnxt_en's RoCE probe via indirect API */
	if (!bp->ulp_probe)
		return ERR_PTR(-EINVAL);

	en_dev = bp->ulp_probe(netdev);
	if (IS_ERR(en_dev))
		return en_dev;

	pdev = en_dev->pdev;
	if (!pdev)
		return ERR_PTR(-EINVAL);

	if (!(en_dev->flags & BNXT_EN_FLAG_ROCE_CAP)) {
		dev_info(&pdev->dev,
			"%s: probe error: RoCE is not supported on this device",
			ROCE_DRV_MODULE_NAME);
		return ERR_PTR(-ENODEV);
	}

	/* Bump net device reference count */
	if (!try_module_get(pdev->driver->driver.owner))
		return ERR_PTR(-ENODEV);

	dev_hold(netdev);

	return en_dev;
}