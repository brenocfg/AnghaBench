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
struct cpsw_common {int rx_ch_num; int /*<<< orphan*/ ** page_pool; TYPE_2__* slaves; TYPE_1__ data; } ;
struct TYPE_4__ {struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpsw_ndev_destroy_xdp_rxq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  page_pool_destroy (int /*<<< orphan*/ *) ; 

void cpsw_destroy_xdp_rxqs(struct cpsw_common *cpsw)
{
	struct net_device *ndev;
	int i, ch;

	for (ch = 0; ch < cpsw->rx_ch_num; ch++) {
		for (i = 0; i < cpsw->data.slaves; i++) {
			ndev = cpsw->slaves[i].ndev;
			if (!ndev)
				continue;

			cpsw_ndev_destroy_xdp_rxq(netdev_priv(ndev), ch);
		}

		page_pool_destroy(cpsw->page_pool[ch]);
		cpsw->page_pool[ch] = NULL;
	}
}