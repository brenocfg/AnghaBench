#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct hnae3_handle {TYPE_2__* ae_algo; TYPE_3__* pdev; } ;
struct TYPE_6__ {int revision; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int (* set_rss ) (struct hnae3_handle*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  const ETH_RSS_HASH_NO_CHANGE ; 
 int /*<<< orphan*/  const ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  const ETH_RSS_HASH_XOR ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int stub1 (struct hnae3_handle*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int hns3_set_rss(struct net_device *netdev, const u32 *indir,
			const u8 *key, const u8 hfunc)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);

	if (!h->ae_algo->ops->set_rss)
		return -EOPNOTSUPP;

	if ((h->pdev->revision == 0x20 &&
	     hfunc != ETH_RSS_HASH_TOP) || (hfunc != ETH_RSS_HASH_NO_CHANGE &&
	     hfunc != ETH_RSS_HASH_TOP && hfunc != ETH_RSS_HASH_XOR)) {
		netdev_err(netdev, "hash func not supported\n");
		return -EOPNOTSUPP;
	}

	if (!indir) {
		netdev_err(netdev,
			   "set rss failed for indir is empty\n");
		return -EOPNOTSUPP;
	}

	return h->ae_algo->ops->set_rss(h, indir, key, hfunc);
}