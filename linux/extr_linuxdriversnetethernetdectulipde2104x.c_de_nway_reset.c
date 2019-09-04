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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct de_private {scalar_t__ media_type; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DE_MEDIA_TP_AUTO ; 
 int EINVAL ; 
 int NWayRestart ; 
 int NWayState ; 
 int /*<<< orphan*/  SIAStatus ; 
 int /*<<< orphan*/  de_link_down (struct de_private*) ; 
 int dr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  link ; 
 struct de_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct de_private*,int /*<<< orphan*/ ,struct net_device*,char*,int,int) ; 

__attribute__((used)) static int de_nway_reset(struct net_device *dev)
{
	struct de_private *de = netdev_priv(dev);
	u32 status;

	if (de->media_type != DE_MEDIA_TP_AUTO)
		return -EINVAL;
	if (netif_carrier_ok(de->dev))
		de_link_down(de);

	status = dr32(SIAStatus);
	dw32(SIAStatus, (status & ~NWayState) | NWayRestart);
	netif_info(de, link, dev, "link nway restart, status %x,%x\n",
		   status, dr32(SIAStatus));
	return 0;
}