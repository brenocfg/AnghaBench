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
struct net_device {int dummy; } ;
struct mvneta_port {int /*<<< orphan*/  phylink; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 int phylink_mii_ioctl (int /*<<< orphan*/ ,struct ifreq*,int) ; 

__attribute__((used)) static int mvneta_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct mvneta_port *pp = netdev_priv(dev);

	return phylink_mii_ioctl(pp->phylink, ifr, cmd);
}