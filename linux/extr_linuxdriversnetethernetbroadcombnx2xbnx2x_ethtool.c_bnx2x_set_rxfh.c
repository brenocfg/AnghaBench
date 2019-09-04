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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__* ind_table; } ;
struct bnx2x {scalar_t__ state; TYPE_2__* fp; TYPE_1__ rss_conf_obj; } ;
struct TYPE_4__ {scalar_t__ const cl_id; } ;

/* Variables and functions */
 scalar_t__ BNX2X_STATE_OPEN ; 
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 size_t T_ETH_INDIRECTION_TABLE_SIZE ; 
 int bnx2x_config_rss_eth (struct bnx2x*,int) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_set_rxfh(struct net_device *dev, const u32 *indir,
			  const u8 *key, const u8 hfunc)
{
	struct bnx2x *bp = netdev_priv(dev);
	size_t i;

	/* We require at least one supported parameter to be changed and no
	 * change in any of the unsupported parameters
	 */
	if (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		return -EOPNOTSUPP;

	if (!indir)
		return 0;

	for (i = 0; i < T_ETH_INDIRECTION_TABLE_SIZE; i++) {
		/*
		 * The same as in bnx2x_get_rxfh: we can't use a memcpy()
		 * as an internal storage of an indirection table is a u8 array
		 * while indir->ring_index points to an array of u32.
		 *
		 * Indirection table contains the FW Client IDs, so we need to
		 * align the received table to the Client ID of the leading RSS
		 * queue
		 */
		bp->rss_conf_obj.ind_table[i] = indir[i] + bp->fp->cl_id;
	}

	if (bp->state == BNX2X_STATE_OPEN)
		return bnx2x_config_rss_eth(bp, false);

	return 0;
}