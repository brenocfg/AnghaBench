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
 int /*<<< orphan*/  gem_do_stop (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_device_present (struct net_device*) ; 

__attribute__((used)) static int gem_close(struct net_device *dev)
{
	if (netif_device_present(dev))
		gem_do_stop(dev, 0);

	return 0;
}