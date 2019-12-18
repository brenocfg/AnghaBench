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
typedef  char u8 ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
#define  MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP 132 
#define  MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP28 131 
#define  MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_DD 130 
#define  MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_PLUS 129 
#define  MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_SFP 128 
 int MLXSW_REG_MCIA_EEPROM_SIZE ; 
 int /*<<< orphan*/  MLXSW_REG_MCIA_I2C_ADDR_LOW ; 
 int MLXSW_REG_MCIA_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_MCIA_PAGE0_LO_OFF ; 
 int /*<<< orphan*/  mcia ; 
 int /*<<< orphan*/  mlxsw_reg_mcia_eeprom_memcpy_from (char*,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mcia_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_query (struct mlxsw_core*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mlxsw_env_validate_cable_ident(struct mlxsw_core *core, int id,
					  bool *qsfp)
{
	char eeprom_tmp[MLXSW_REG_MCIA_EEPROM_SIZE];
	char mcia_pl[MLXSW_REG_MCIA_LEN];
	u8 ident;
	int err;

	mlxsw_reg_mcia_pack(mcia_pl, id, 0, MLXSW_REG_MCIA_PAGE0_LO_OFF, 0, 1,
			    MLXSW_REG_MCIA_I2C_ADDR_LOW);
	err = mlxsw_reg_query(core, MLXSW_REG(mcia), mcia_pl);
	if (err)
		return err;
	mlxsw_reg_mcia_eeprom_memcpy_from(mcia_pl, eeprom_tmp);
	ident = eeprom_tmp[0];
	switch (ident) {
	case MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_SFP:
		*qsfp = false;
		break;
	case MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP: /* fall-through */
	case MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_PLUS: /* fall-through */
	case MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP28: /* fall-through */
	case MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_DD:
		*qsfp = true;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}