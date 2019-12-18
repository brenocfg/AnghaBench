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
struct tun_struct {int align; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NET_SKB_PAD ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void tun_set_headroom(struct net_device *dev, int new_hr)
{
	struct tun_struct *tun = netdev_priv(dev);

	if (new_hr < NET_SKB_PAD)
		new_hr = NET_SKB_PAD;

	tun->align = new_hr;
}