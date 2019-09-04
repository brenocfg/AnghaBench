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
struct net_device {unsigned char* dev_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  is_local_ether_addr (unsigned char*) ; 
 scalar_t__ is_multicast_ether_addr (unsigned char*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (unsigned char*) ; 
 int /*<<< orphan*/  mac_pton (char*,unsigned char*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_etheraddr(struct net_device *dev, char *str)
{
	unsigned char *addr = dev->dev_addr;

	if (str == NULL)
		goto random;

	if (!mac_pton(str, addr)) {
		pr_err("%s: failed to parse '%s' as an ethernet address\n",
		       dev->name, str);
		goto random;
	}
	if (is_multicast_ether_addr(addr)) {
		pr_err("%s: attempt to assign a multicast ethernet address\n",
		       dev->name);
		goto random;
	}
	if (!is_valid_ether_addr(addr)) {
		pr_err("%s: attempt to assign an invalid ethernet address\n",
		       dev->name);
		goto random;
	}
	if (!is_local_ether_addr(addr))
		pr_warn("%s: assigning a globally valid ethernet address\n",
			dev->name);
	return;

random:
	pr_info("%s: choosing a random ethernet address\n",
		dev->name);
	eth_hw_addr_random(dev);
}