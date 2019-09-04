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
struct mlxcpld_i2c_priv {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int MLXCPLD_LPCI2C_ACK_IND ; 
 int MLXCPLD_LPCI2C_NACK_IND ; 
 int MLXCPLD_LPCI2C_NO_IND ; 
 int MLXCPLD_LPCI2C_STATUS_NACK ; 
 int /*<<< orphan*/  MLXCPLD_LPCI2C_STATUS_REG ; 
 int MLXCPLD_LPCI2C_TRANS_END ; 
 int /*<<< orphan*/  mlxcpld_i2c_read_comm (struct mlxcpld_i2c_priv*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int mlxcpld_i2c_check_status(struct mlxcpld_i2c_priv *priv, int *status)
{
	u8 val;

	mlxcpld_i2c_read_comm(priv, MLXCPLD_LPCI2C_STATUS_REG, &val, 1);

	if (val & MLXCPLD_LPCI2C_TRANS_END) {
		if (val & MLXCPLD_LPCI2C_STATUS_NACK)
			/*
			 * The slave is unable to accept the data. No such
			 * slave, command not understood, or unable to accept
			 * any more data.
			 */
			*status = MLXCPLD_LPCI2C_NACK_IND;
		else
			*status = MLXCPLD_LPCI2C_ACK_IND;
		return 0;
	}
	*status = MLXCPLD_LPCI2C_NO_IND;

	return -EIO;
}