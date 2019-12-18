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
struct mlxsw_core {int dummy; } ;
struct ethtool_eeprom {int offset; int len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlxsw_env_query_module_eeprom (struct mlxsw_core*,int,int,int,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 

int mlxsw_env_get_module_eeprom(struct net_device *netdev,
				struct mlxsw_core *mlxsw_core, int module,
				struct ethtool_eeprom *ee, u8 *data)
{
	int offset = ee->offset;
	unsigned int read_size;
	int i = 0;
	int err;

	if (!ee->len)
		return -EINVAL;

	memset(data, 0, ee->len);

	while (i < ee->len) {
		err = mlxsw_env_query_module_eeprom(mlxsw_core, module, offset,
						    ee->len - i, data + i,
						    &read_size);
		if (err) {
			netdev_err(netdev, "Eeprom query failed\n");
			return err;
		}

		i += read_size;
		offset += read_size;
	}

	return 0;
}