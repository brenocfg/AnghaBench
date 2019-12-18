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
struct sk_buff {int dummy; } ;
struct nxp_nci_info {scalar_t__ mode; int /*<<< orphan*/  phy_id; TYPE_1__* phy_ops; } ;
struct nci_dev {int dummy; } ;
struct TYPE_2__ {int (* write ) (int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 scalar_t__ NXP_NCI_MODE_NCI ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nxp_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int nxp_nci_send(struct nci_dev *ndev, struct sk_buff *skb)
{
	struct nxp_nci_info *info = nci_get_drvdata(ndev);
	int r;

	if (!info->phy_ops->write) {
		r = -ENOTSUPP;
		goto send_exit;
	}

	if (info->mode != NXP_NCI_MODE_NCI) {
		r = -EINVAL;
		goto send_exit;
	}

	r = info->phy_ops->write(info->phy_id, skb);
	if (r < 0)
		kfree_skb(skb);

send_exit:
	return r;
}