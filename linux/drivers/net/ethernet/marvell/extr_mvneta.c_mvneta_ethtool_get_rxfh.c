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
struct mvneta_port {int /*<<< orphan*/  indir; scalar_t__ neta_armada3700; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  MVNETA_RSS_LU_TABLE_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mvneta_ethtool_get_rxfh(struct net_device *dev, u32 *indir, u8 *key,
				   u8 *hfunc)
{
	struct mvneta_port *pp = netdev_priv(dev);

	/* Current code for Armada 3700 doesn't support RSS features yet */
	if (pp->neta_armada3700)
		return -EOPNOTSUPP;

	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	if (!indir)
		return 0;

	memcpy(indir, pp->indir, MVNETA_RSS_LU_TABLE_SIZE);

	return 0;
}