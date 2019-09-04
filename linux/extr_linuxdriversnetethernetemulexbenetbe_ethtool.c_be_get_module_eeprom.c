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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {scalar_t__ offset; scalar_t__ len; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MAX_PRIVILEGES ; 
 scalar_t__ PAGE_DATA_LEN ; 
 int /*<<< orphan*/  TR_PAGE_A0 ; 
 int /*<<< orphan*/  TR_PAGE_A2 ; 
 int be_cmd_read_port_transceiver_data (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int be_cmd_status (int) ; 
 int /*<<< orphan*/  check_privilege (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_get_module_eeprom(struct net_device *netdev,
				struct ethtool_eeprom *eeprom, u8 *data)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	int status;

	if (!check_privilege(adapter, MAX_PRIVILEGES))
		return -EOPNOTSUPP;

	status = be_cmd_read_port_transceiver_data(adapter, TR_PAGE_A0,
						   data);
	if (status)
		goto err;

	if (eeprom->offset + eeprom->len > PAGE_DATA_LEN) {
		status = be_cmd_read_port_transceiver_data(adapter,
							   TR_PAGE_A2,
							   data +
							   PAGE_DATA_LEN);
		if (status)
			goto err;
	}
	if (eeprom->offset)
		memcpy(data, data + eeprom->offset, eeprom->len);
err:
	return be_cmd_status(status);
}