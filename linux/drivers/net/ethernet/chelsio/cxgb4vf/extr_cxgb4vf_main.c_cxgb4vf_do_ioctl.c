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
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int cxgb4vf_do_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	int ret = 0;

	switch (cmd) {
	    /*
	     * The VF Driver doesn't have access to any of the other
	     * common Ethernet device ioctl()'s (like reading/writing
	     * PHY registers, etc.
	     */

	default:
		ret = -EOPNOTSUPP;
		break;
	}
	return ret;
}