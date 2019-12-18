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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_i2c {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int mlxsw_i2c_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*,size_t,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_i2c_cmd_exec(void *bus_priv, u16 opcode, u8 opcode_mod,
			      u32 in_mod, bool out_mbox_direct,
			      char *in_mbox, size_t in_mbox_size,
			      char *out_mbox, size_t out_mbox_size,
			      u8 *status)
{
	struct mlxsw_i2c *mlxsw_i2c = bus_priv;

	return mlxsw_i2c_cmd(mlxsw_i2c->dev, opcode, in_mod, in_mbox_size,
			     in_mbox, out_mbox_size, out_mbox, status);
}