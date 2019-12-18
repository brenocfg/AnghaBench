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
struct net_device {int dummy; } ;
struct TYPE_3__ {int slaves; } ;
struct cpsw_common {int rx_ch_num; TYPE_2__* slaves; TYPE_1__ data; } ;
struct TYPE_4__ {struct net_device* ndev; } ;

/* Variables and functions */
 int cpsw_create_rx_pool (struct cpsw_common*,int) ; 
 int /*<<< orphan*/  cpsw_destroy_xdp_rxqs (struct cpsw_common*) ; 
 int cpsw_ndev_create_xdp_rxq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

int cpsw_create_xdp_rxqs(struct cpsw_common *cpsw)
{
	struct net_device *ndev;
	int i, ch, ret;

	for (ch = 0; ch < cpsw->rx_ch_num; ch++) {
		ret = cpsw_create_rx_pool(cpsw, ch);
		if (ret)
			goto err_cleanup;

		/* using same page pool is allowed as no running rx handlers
		 * simultaneously for both ndevs
		 */
		for (i = 0; i < cpsw->data.slaves; i++) {
			ndev = cpsw->slaves[i].ndev;
			if (!ndev)
				continue;

			ret = cpsw_ndev_create_xdp_rxq(netdev_priv(ndev), ch);
			if (ret)
				goto err_cleanup;
		}
	}

	return 0;

err_cleanup:
	cpsw_destroy_xdp_rxqs(cpsw);

	return ret;
}