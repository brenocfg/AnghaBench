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
struct mlxsw_sp_port {int /*<<< orphan*/  dev; } ;
struct ethtool_eeprom {int offset; int len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlxsw_sp_query_module_eeprom (struct mlxsw_sp_port*,int,int,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_get_module_eeprom(struct net_device *netdev,
				      struct ethtool_eeprom *ee,
				      u8 *data)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(netdev);
	int offset = ee->offset;
	unsigned int read_size;
	int i = 0;
	int err;

	if (!ee->len)
		return -EINVAL;

	memset(data, 0, ee->len);

	while (i < ee->len) {
		err = mlxsw_sp_query_module_eeprom(mlxsw_sp_port, offset,
						   ee->len - i, data + i,
						   &read_size);
		if (err) {
			netdev_err(mlxsw_sp_port->dev, "Eeprom query failed\n");
			return err;
		}

		i += read_size;
		offset += read_size;
	}

	return 0;
}