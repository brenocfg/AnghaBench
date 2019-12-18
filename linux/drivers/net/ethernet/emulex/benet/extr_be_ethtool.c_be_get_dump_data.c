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
struct ethtool_dump {int /*<<< orphan*/  len; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MAX_PRIVILEGES ; 
 int be_cmd_status (int) ; 
 int be_read_dump_data (struct be_adapter*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  check_privilege (struct be_adapter*,int /*<<< orphan*/ ) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
be_get_dump_data(struct net_device *netdev, struct ethtool_dump *dump,
		 void *buf)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	int status;

	if (!check_privilege(adapter, MAX_PRIVILEGES))
		return -EOPNOTSUPP;

	status = be_read_dump_data(adapter, dump->len, buf);
	return be_cmd_status(status);
}