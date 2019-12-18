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
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct if_phonet_req {TYPE_1__ ifr_phonet_autoconf; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  PN_DEV_PC ; 
#define  SIOCPNGAUTOCONF 128 

__attribute__((used)) static int usbpn_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct if_phonet_req *req = (struct if_phonet_req *)ifr;

	switch (cmd) {
	case SIOCPNGAUTOCONF:
		req->ifr_phonet_autoconf.device = PN_DEV_PC;
		return 0;
	}
	return -ENOIOCTLCMD;
}