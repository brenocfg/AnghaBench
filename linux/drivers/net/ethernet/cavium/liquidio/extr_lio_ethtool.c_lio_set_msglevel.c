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
struct lio {int msg_enable; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 int NETIF_MSG_HW ; 
 int /*<<< orphan*/  OCTNET_CMD_VERBOSE_DISABLE ; 
 int /*<<< orphan*/  OCTNET_CMD_VERBOSE_ENABLE ; 
 int /*<<< orphan*/  liquidio_set_feature (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lio_set_msglevel(struct net_device *netdev, u32 msglvl)
{
	struct lio *lio = GET_LIO(netdev);

	if ((msglvl ^ lio->msg_enable) & NETIF_MSG_HW) {
		if (msglvl & NETIF_MSG_HW)
			liquidio_set_feature(netdev,
					     OCTNET_CMD_VERBOSE_ENABLE, 0);
		else
			liquidio_set_feature(netdev,
					     OCTNET_CMD_VERBOSE_DISABLE, 0);
	}

	lio->msg_enable = msglvl;
}