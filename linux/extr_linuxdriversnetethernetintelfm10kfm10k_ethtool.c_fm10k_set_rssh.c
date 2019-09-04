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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct fm10k_hw {int dummy; } ;
struct fm10k_intfc {scalar_t__* rssrk; struct fm10k_hw hw; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  FM10K_RSSRK (int /*<<< orphan*/ ,int) ; 
 int FM10K_RSSRK_SIZE ; 
 int fm10k_set_reta (struct net_device*,scalar_t__ const*) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int fm10k_set_rssh(struct net_device *netdev, const u32 *indir,
			  const u8 *key, const u8 hfunc)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);
	struct fm10k_hw *hw = &interface->hw;
	int i, err;

	/* We do not allow change in unsupported parameters */
	if (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		return -EOPNOTSUPP;

	err = fm10k_set_reta(netdev, indir);
	if (err || !key)
		return err;

	for (i = 0; i < FM10K_RSSRK_SIZE; i++, key += 4) {
		u32 rssrk = le32_to_cpu(*(__le32 *)key);

		if (interface->rssrk[i] == rssrk)
			continue;

		interface->rssrk[i] = rssrk;
		fm10k_write_reg(hw, FM10K_RSSRK(0, i), rssrk);
	}

	return 0;
}