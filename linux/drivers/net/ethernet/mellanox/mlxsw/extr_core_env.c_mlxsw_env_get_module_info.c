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
typedef  unsigned int u16 ;
struct mlxsw_core {int dummy; } ;
struct ethtool_modinfo {int eeprom_len; void* type; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 void* ETH_MODULE_SFF_8436 ; 
 void* ETH_MODULE_SFF_8436_LEN ; 
 void* ETH_MODULE_SFF_8472 ; 
 int ETH_MODULE_SFF_8472_LEN ; 
 void* ETH_MODULE_SFF_8636 ; 
 int ETH_MODULE_SFF_8636_LEN ; 
 size_t MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID ; 
#define  MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP 131 
#define  MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP28 130 
#define  MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_PLUS 129 
#define  MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_SFP 128 
 size_t MLXSW_REG_MCIA_EEPROM_MODULE_INFO_REV_ID ; 
 int MLXSW_REG_MCIA_EEPROM_MODULE_INFO_REV_ID_8636 ; 
 int MLXSW_REG_MCIA_EEPROM_MODULE_INFO_SIZE ; 
 int /*<<< orphan*/  SFP_DIAGMON ; 
 int mlxsw_env_query_module_eeprom (struct mlxsw_core*,int,int /*<<< orphan*/ ,int,int*,unsigned int*) ; 

int mlxsw_env_get_module_info(struct mlxsw_core *mlxsw_core, int module,
			      struct ethtool_modinfo *modinfo)
{
	u8 module_info[MLXSW_REG_MCIA_EEPROM_MODULE_INFO_SIZE];
	u16 offset = MLXSW_REG_MCIA_EEPROM_MODULE_INFO_SIZE;
	u8 module_rev_id, module_id, diag_mon;
	unsigned int read_size;
	int err;

	err = mlxsw_env_query_module_eeprom(mlxsw_core, module, 0, offset,
					    module_info, &read_size);
	if (err)
		return err;

	if (read_size < offset)
		return -EIO;

	module_rev_id = module_info[MLXSW_REG_MCIA_EEPROM_MODULE_INFO_REV_ID];
	module_id = module_info[MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID];

	switch (module_id) {
	case MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP:
		modinfo->type       = ETH_MODULE_SFF_8436;
		modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		break;
	case MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_PLUS: /* fall-through */
	case MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP28:
		if (module_id == MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP28 ||
		    module_rev_id >=
		    MLXSW_REG_MCIA_EEPROM_MODULE_INFO_REV_ID_8636) {
			modinfo->type       = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		} else {
			modinfo->type       = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		}
		break;
	case MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_SFP:
		/* Verify if transceiver provides diagnostic monitoring page */
		err = mlxsw_env_query_module_eeprom(mlxsw_core, module,
						    SFP_DIAGMON, 1, &diag_mon,
						    &read_size);
		if (err)
			return err;

		if (read_size < 1)
			return -EIO;

		modinfo->type       = ETH_MODULE_SFF_8472;
		if (diag_mon)
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		else
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN / 2;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}