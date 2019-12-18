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
 int hdlc_ioctl (struct net_device*,struct ifreq*,int) ; 

__attribute__((used)) static int sealevel_ioctl(struct net_device *d, struct ifreq *ifr, int cmd)
{
	/* struct slvl_device *slvl=dev_to_chan(d);
	   z8530_ioctl(d,&slvl->sync.chanA,ifr,cmd) */
	return hdlc_ioctl(d, ifr, cmd);
}