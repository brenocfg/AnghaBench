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
typedef  enum mlxsw_reg_ptys_connector_type { ____Placeholder_mlxsw_reg_ptys_connector_type } mlxsw_reg_ptys_connector_type ;

/* Variables and functions */
#define  MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_AUI 136 
#define  MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_BNC 135 
#define  MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_DA 134 
#define  MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_FIBRE 133 
#define  MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_MII 132 
#define  MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_NONE 131 
#define  MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_OTHER 130 
#define  MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_TP 129 
#define  MLXSW_REG_PTYS_CONNECTOR_TYPE_UNKNOWN_OR_NO_CONNECTOR 128 
 int /*<<< orphan*/  PORT_AUI ; 
 int /*<<< orphan*/  PORT_BNC ; 
 int /*<<< orphan*/  PORT_DA ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_MII ; 
 int /*<<< orphan*/  PORT_NONE ; 
 int /*<<< orphan*/  PORT_OTHER ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static u8
mlxsw_sp_port_connector_port(enum mlxsw_reg_ptys_connector_type connector_type)
{
	switch (connector_type) {
	case MLXSW_REG_PTYS_CONNECTOR_TYPE_UNKNOWN_OR_NO_CONNECTOR:
		return PORT_OTHER;
	case MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_NONE:
		return PORT_NONE;
	case MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_TP:
		return PORT_TP;
	case MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_AUI:
		return PORT_AUI;
	case MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_BNC:
		return PORT_BNC;
	case MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_MII:
		return PORT_MII;
	case MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_FIBRE:
		return PORT_FIBRE;
	case MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_DA:
		return PORT_DA;
	case MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_OTHER:
		return PORT_OTHER;
	default:
		WARN_ON_ONCE(1);
		return PORT_OTHER;
	}
}