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
struct net_device {int /*<<< orphan*/  tstats; } ;
struct gtp_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtp_encap_disable (struct gtp_dev*) ; 
 struct gtp_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void gtp_dev_uninit(struct net_device *dev)
{
	struct gtp_dev *gtp = netdev_priv(dev);

	gtp_encap_disable(gtp);
	free_percpu(dev->tstats);
}