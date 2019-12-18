#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int mb_off_in; int mb_size_in; int mb_off_out; int mb_size_out; } ;
struct mlxsw_i2c {TYPE_1__ cmd; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int GENMASK (int,int) ; 
 int MLXSW_I2C_ADDR_WIDTH ; 
 int MLXSW_I2C_MBOX_OFFSET_BITS ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
mlxsw_i2c_convert_mbox(struct mlxsw_i2c *mlxsw_i2c, u8 *buf)
{
	u32 tmp;

	/* Local in/out mailboxes: 20 bits for offset, 12 for size */
	tmp = be32_to_cpup((__be32 *) buf);
	mlxsw_i2c->cmd.mb_off_in = tmp &
				   GENMASK(MLXSW_I2C_MBOX_OFFSET_BITS - 1, 0);
	mlxsw_i2c->cmd.mb_size_in = (tmp & GENMASK(31,
					MLXSW_I2C_MBOX_OFFSET_BITS)) >>
					MLXSW_I2C_MBOX_OFFSET_BITS;

	tmp = be32_to_cpup((__be32 *) (buf + MLXSW_I2C_ADDR_WIDTH));
	mlxsw_i2c->cmd.mb_off_out = tmp &
				    GENMASK(MLXSW_I2C_MBOX_OFFSET_BITS - 1, 0);
	mlxsw_i2c->cmd.mb_size_out = (tmp & GENMASK(31,
					MLXSW_I2C_MBOX_OFFSET_BITS)) >>
					MLXSW_I2C_MBOX_OFFSET_BITS;
}