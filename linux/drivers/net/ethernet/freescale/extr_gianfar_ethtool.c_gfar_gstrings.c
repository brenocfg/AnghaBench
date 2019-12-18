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
struct gfar_private {int device_flags; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int FSL_GIANFAR_DEV_HAS_RMON ; 
 int GFAR_EXTRA_STATS_LEN ; 
 int GFAR_STATS_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stat_gstrings ; 

__attribute__((used)) static void gfar_gstrings(struct net_device *dev, u32 stringset, u8 * buf)
{
	struct gfar_private *priv = netdev_priv(dev);

	if (priv->device_flags & FSL_GIANFAR_DEV_HAS_RMON)
		memcpy(buf, stat_gstrings, GFAR_STATS_LEN * ETH_GSTRING_LEN);
	else
		memcpy(buf, stat_gstrings,
		       GFAR_EXTRA_STATS_LEN * ETH_GSTRING_LEN);
}