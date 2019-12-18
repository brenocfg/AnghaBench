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
struct ethtool_regs {int /*<<< orphan*/  version; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mk_adap_vers (struct adapter*) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int /*<<< orphan*/  t4_get_regs (struct adapter*,void*,size_t) ; 
 size_t t4_get_regs_len (struct adapter*) ; 

__attribute__((used)) static void get_regs(struct net_device *dev, struct ethtool_regs *regs,
		     void *buf)
{
	struct adapter *adap = netdev2adap(dev);
	size_t buf_size;

	buf_size = t4_get_regs_len(adap);
	regs->version = mk_adap_vers(adap);
	t4_get_regs(adap, buf, buf_size);
}