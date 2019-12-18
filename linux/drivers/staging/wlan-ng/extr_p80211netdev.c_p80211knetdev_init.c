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

/* Variables and functions */

__attribute__((used)) static int p80211knetdev_init(struct net_device *netdev)
{
	/* Called in response to register_netdev */
	/* This is usually the probe function, but the probe has */
	/* already been done by the MSD and the create_kdev */
	/* function.  All we do here is return success */
	return 0;
}