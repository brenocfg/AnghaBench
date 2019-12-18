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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mvpp2_port {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_RSS_HASH_CRC32 ; 
 int mvpp22_port_rss_ctx_indir_get (struct mvpp2_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp22_rss_is_supported () ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mvpp2_ethtool_get_rxfh(struct net_device *dev, u32 *indir, u8 *key,
				  u8 *hfunc)
{
	struct mvpp2_port *port = netdev_priv(dev);
	int ret = 0;

	if (!mvpp22_rss_is_supported())
		return -EOPNOTSUPP;

	if (indir)
		ret = mvpp22_port_rss_ctx_indir_get(port, 0, indir);

	if (hfunc)
		*hfunc = ETH_RSS_HASH_CRC32;

	return ret;
}