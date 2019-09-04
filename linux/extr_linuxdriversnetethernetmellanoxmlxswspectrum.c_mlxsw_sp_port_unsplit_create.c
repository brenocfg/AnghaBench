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
typedef  size_t u8 ;
struct mlxsw_sp {scalar_t__* port_to_module; } ;

/* Variables and functions */
 size_t MLXSW_PORT_MODULE_MAX_WIDTH ; 
 int /*<<< orphan*/  mlxsw_sp_port_create (struct mlxsw_sp*,size_t,int,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_port_unsplit_create(struct mlxsw_sp *mlxsw_sp,
					 u8 base_port, unsigned int count)
{
	u8 local_port, module, width = MLXSW_PORT_MODULE_MAX_WIDTH;
	int i;

	/* Split by four means we need to re-create two ports, otherwise
	 * only one.
	 */
	count = count / 2;

	for (i = 0; i < count; i++) {
		local_port = base_port + i * 2;
		if (mlxsw_sp->port_to_module[local_port] < 0)
			continue;
		module = mlxsw_sp->port_to_module[local_port];

		mlxsw_sp_port_create(mlxsw_sp, local_port, false, module,
				     width, 0);
	}
}