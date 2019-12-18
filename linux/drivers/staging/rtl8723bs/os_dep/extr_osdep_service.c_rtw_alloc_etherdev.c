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
struct rtw_netdev_priv_indicator {int sizeof_priv; int /*<<< orphan*/  priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_device* alloc_etherdev_mq (int,int) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct rtw_netdev_priv_indicator* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vzalloc (int) ; 

struct net_device *rtw_alloc_etherdev(int sizeof_priv)
{
	struct net_device *pnetdev;
	struct rtw_netdev_priv_indicator *pnpi;

	pnetdev = alloc_etherdev_mq(sizeof(struct rtw_netdev_priv_indicator), 4);
	if (!pnetdev)
		goto RETURN;

	pnpi = netdev_priv(pnetdev);

	pnpi->priv = vzalloc(sizeof_priv);
	if (!pnpi->priv) {
		free_netdev(pnetdev);
		pnetdev = NULL;
		goto RETURN;
	}

	pnpi->sizeof_priv = sizeof_priv;
RETURN:
	return pnetdev;
}