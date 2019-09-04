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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct net_device {int dummy; } ;
struct iw_cm_id {int /*<<< orphan*/  m_remote_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 struct net_device* ip_dev_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_loopback_dst(struct iw_cm_id *cm_id)
{
	struct net_device *dev;
	struct sockaddr_in *raddr = (struct sockaddr_in *)&cm_id->m_remote_addr;

	dev = ip_dev_find(&init_net, raddr->sin_addr.s_addr);
	if (!dev)
		return 0;
	dev_put(dev);
	return 1;
}