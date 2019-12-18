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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mvpp2_port {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_CRC32 ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 int mvpp22_port_rss_ctx_indir_set (struct mvpp2_port*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mvpp22_rss_is_supported () ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mvpp2_ethtool_set_rxfh(struct net_device *dev, const u32 *indir,
				  const u8 *key, const u8 hfunc)
{
	struct mvpp2_port *port = netdev_priv(dev);
	int ret = 0;

	if (!mvpp22_rss_is_supported())
		return -EOPNOTSUPP;

	if (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_CRC32)
		return -EOPNOTSUPP;

	if (key)
		return -EOPNOTSUPP;

	if (indir)
		ret = mvpp22_port_rss_ctx_indir_set(port, 0, indir);

	return ret;
}