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
struct TYPE_2__ {int /*<<< orphan*/  num_rx_rings; } ;
struct nfp_net {TYPE_1__ dp; int /*<<< orphan*/ * rss_itbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ethtool_rxfh_indir_default (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_rss_init_itbl(struct nfp_net *nn)
{
	int i;

	for (i = 0; i < sizeof(nn->rss_itbl); i++)
		nn->rss_itbl[i] =
			ethtool_rxfh_indir_default(i, nn->dp.num_rx_rings);
}