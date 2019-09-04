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
struct net_device {int dummy; } ;
struct bnxt_en_dev {int /*<<< orphan*/  pdev; struct net_device* net; int /*<<< orphan*/  flags; int /*<<< orphan*/ * en_ops; } ;
struct bnxt {int flags; struct bnxt_en_dev* edev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_EN_FLAG_ROCEV1_CAP ; 
 int /*<<< orphan*/  BNXT_EN_FLAG_ROCEV2_CAP ; 
 int BNXT_FLAG_ROCEV1_CAP ; 
 int BNXT_FLAG_ROCEV2_CAP ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct bnxt_en_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bnxt_en_ops_tbl ; 
 struct bnxt_en_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

struct bnxt_en_dev *bnxt_ulp_probe(struct net_device *dev)
{
	struct bnxt *bp = netdev_priv(dev);
	struct bnxt_en_dev *edev;

	edev = bp->edev;
	if (!edev) {
		edev = kzalloc(sizeof(*edev), GFP_KERNEL);
		if (!edev)
			return ERR_PTR(-ENOMEM);
		edev->en_ops = &bnxt_en_ops_tbl;
		if (bp->flags & BNXT_FLAG_ROCEV1_CAP)
			edev->flags |= BNXT_EN_FLAG_ROCEV1_CAP;
		if (bp->flags & BNXT_FLAG_ROCEV2_CAP)
			edev->flags |= BNXT_EN_FLAG_ROCEV2_CAP;
		edev->net = dev;
		edev->pdev = bp->pdev;
		bp->edev = edev;
	}
	return bp->edev;
}