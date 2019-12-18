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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct port_info {unsigned int rss_size; int /*<<< orphan*/ * rss; TYPE_1__* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CXGB4_FULL_INIT_DONE ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 int cxgb4_write_rss (struct port_info*,int /*<<< orphan*/ *) ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int set_rss_table(struct net_device *dev, const u32 *p, const u8 *key,
			 const u8 hfunc)
{
	unsigned int i;
	struct port_info *pi = netdev_priv(dev);

	/* We require at least one supported parameter to be changed and no
	 * change in any of the unsupported parameters
	 */
	if (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		return -EOPNOTSUPP;
	if (!p)
		return 0;

	/* Interface must be brought up atleast once */
	if (pi->adapter->flags & CXGB4_FULL_INIT_DONE) {
		for (i = 0; i < pi->rss_size; i++)
			pi->rss[i] = p[i];

		return cxgb4_write_rss(pi, pi->rss);
	}

	return -EPERM;
}