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
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct in_ifaddr {TYPE_2__* ifa_dev; int /*<<< orphan*/  ifa_address; } ;
struct TYPE_4__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int addr_event (struct notifier_block*,unsigned long,struct sockaddr*,struct net_device*) ; 

__attribute__((used)) static int inetaddr_event(struct notifier_block *this, unsigned long event,
			  void *ptr)
{
	struct sockaddr_in	in;
	struct net_device	*ndev;
	struct in_ifaddr	*ifa = ptr;

	in.sin_family = AF_INET;
	in.sin_addr.s_addr = ifa->ifa_address;
	ndev = ifa->ifa_dev->dev;

	return addr_event(this, event, (struct sockaddr *)&in, ndev);
}