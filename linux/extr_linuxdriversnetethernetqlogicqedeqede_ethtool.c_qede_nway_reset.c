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
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_2__* ops; } ;
struct qed_link_params {int link_up; } ;
struct qed_link_output {int link_up; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  link_params ;
typedef  int /*<<< orphan*/  current_link ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_link ) (int /*<<< orphan*/ ,struct qed_link_params*) ;int /*<<< orphan*/  (* get_link ) (int /*<<< orphan*/ ,struct qed_link_params*) ;int /*<<< orphan*/  (* can_link_change ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  memset (struct qed_link_params*,int /*<<< orphan*/ ,int) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct qed_link_params*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct qed_link_params*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,struct qed_link_params*) ; 

__attribute__((used)) static int qede_nway_reset(struct net_device *dev)
{
	struct qede_dev *edev = netdev_priv(dev);
	struct qed_link_output current_link;
	struct qed_link_params link_params;

	if (!edev->ops || !edev->ops->common->can_link_change(edev->cdev)) {
		DP_INFO(edev, "Link settings are not allowed to be changed\n");
		return -EOPNOTSUPP;
	}

	if (!netif_running(dev))
		return 0;

	memset(&current_link, 0, sizeof(current_link));
	edev->ops->common->get_link(edev->cdev, &current_link);
	if (!current_link.link_up)
		return 0;

	/* Toggle the link */
	memset(&link_params, 0, sizeof(link_params));
	link_params.link_up = false;
	edev->ops->common->set_link(edev->cdev, &link_params);
	link_params.link_up = true;
	edev->ops->common->set_link(edev->cdev, &link_params);

	return 0;
}