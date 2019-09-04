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
struct port_info {unsigned int rss_size; int /*<<< orphan*/ * rss; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int get_rss_table(struct net_device *dev, u32 *p, u8 *key, u8 *hfunc)
{
	const struct port_info *pi = netdev_priv(dev);
	unsigned int n = pi->rss_size;

	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	if (!p)
		return 0;
	while (n--)
		p[n] = pi->rss[n];
	return 0;
}