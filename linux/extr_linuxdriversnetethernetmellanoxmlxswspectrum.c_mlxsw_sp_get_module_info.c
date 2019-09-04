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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port {int dummy; } ;
struct ethtool_modinfo {void* eeprom_len; void* type; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 void* ETH_MODULE_SFF_8436 ; 
 void* ETH_MODULE_SFF_8436_LEN ; 
 void* ETH_MODULE_SFF_8472 ; 
 void* ETH_MODULE_SFF_8472_LEN ; 
 void* ETH_MODULE_SFF_8636 ; 
 void* ETH_MODULE_SFF_8636_LEN ; 
 size_t MLXSW_SP_EEPROM_MODULE_INFO_ID ; 
#define  MLXSW_SP_EEPROM_MODULE_INFO_ID_QSFP 131 
#define  MLXSW_SP_EEPROM_MODULE_INFO_ID_QSFP28 130 
#define  MLXSW_SP_EEPROM_MODULE_INFO_ID_QSFP_PLUS 129 
#define  MLXSW_SP_EEPROM_MODULE_INFO_ID_SFP 128 
 size_t MLXSW_SP_EEPROM_MODULE_INFO_REV_ID ; 
 int MLXSW_SP_EEPROM_MODULE_INFO_REV_ID_8636 ; 
 int MLXSW_SP_EEPROM_MODULE_INFO_SIZE ; 
 int mlxsw_sp_query_module_eeprom (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int,int*,unsigned int*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_get_module_info(struct net_device *netdev,
				    struct ethtool_modinfo *modinfo)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(netdev);
	u8 module_info[MLXSW_SP_EEPROM_MODULE_INFO_SIZE];
	u8 module_rev_id, module_id;
	unsigned int read_size;
	int err;

	err = mlxsw_sp_query_module_eeprom(mlxsw_sp_port, 0,
					   MLXSW_SP_EEPROM_MODULE_INFO_SIZE,
					   module_info, &read_size);
	if (err)
		return err;

	if (read_size < MLXSW_SP_EEPROM_MODULE_INFO_SIZE)
		return -EIO;

	module_rev_id = module_info[MLXSW_SP_EEPROM_MODULE_INFO_REV_ID];
	module_id = module_info[MLXSW_SP_EEPROM_MODULE_INFO_ID];

	switch (module_id) {
	case MLXSW_SP_EEPROM_MODULE_INFO_ID_QSFP:
		modinfo->type       = ETH_MODULE_SFF_8436;
		modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		break;
	case MLXSW_SP_EEPROM_MODULE_INFO_ID_QSFP_PLUS:
	case MLXSW_SP_EEPROM_MODULE_INFO_ID_QSFP28:
		if (module_id  == MLXSW_SP_EEPROM_MODULE_INFO_ID_QSFP28 ||
		    module_rev_id >= MLXSW_SP_EEPROM_MODULE_INFO_REV_ID_8636) {
			modinfo->type       = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		} else {
			modinfo->type       = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		}
		break;
	case MLXSW_SP_EEPROM_MODULE_INFO_ID_SFP:
		modinfo->type       = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}