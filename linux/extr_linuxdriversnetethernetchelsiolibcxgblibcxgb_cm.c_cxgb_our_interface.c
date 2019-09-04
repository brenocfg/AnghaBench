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
struct cxgb4_lld_info {int nports; struct net_device** ports; } ;

/* Variables and functions */

__attribute__((used)) static bool
cxgb_our_interface(struct cxgb4_lld_info *lldi,
		   struct net_device *(*get_real_dev)(struct net_device *),
		   struct net_device *egress_dev)
{
	int i;

	egress_dev = get_real_dev(egress_dev);
	for (i = 0; i < lldi->nports; i++)
		if (lldi->ports[i] == egress_dev)
			return true;
	return false;
}