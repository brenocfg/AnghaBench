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
struct hnae3_handle {TYPE_2__* pdev; TYPE_1__* ae_algo; } ;
struct hnae3_ae_ops {int /*<<< orphan*/  (* get_fec ) (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct ethtool_fecparam {void* active_fec; void* fec; } ;
struct TYPE_4__ {int revision; } ;
struct TYPE_3__ {struct hnae3_ae_ops* ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 void* loc_to_eth_fec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns3_get_fecparam(struct net_device *netdev,
			     struct ethtool_fecparam *fec)
{
	struct hnae3_handle *handle = hns3_get_handle(netdev);
	const struct hnae3_ae_ops *ops = handle->ae_algo->ops;
	u8 fec_ability;
	u8 fec_mode;

	if (handle->pdev->revision == 0x20)
		return -EOPNOTSUPP;

	if (!ops->get_fec)
		return -EOPNOTSUPP;

	ops->get_fec(handle, &fec_ability, &fec_mode);

	fec->fec = loc_to_eth_fec(fec_ability);
	fec->active_fec = loc_to_eth_fec(fec_mode);

	return 0;
}