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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mcda ; 
 int /*<<< orphan*/  mlxsw_reg_mcda_data_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcda_offset_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcda_size_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mcda_update_handle_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_mcda_pack(char *payload, u32 update_handle,
				       u32 offset, u16 size, u8 *data)
{
	int i;

	MLXSW_REG_ZERO(mcda, payload);
	mlxsw_reg_mcda_update_handle_set(payload, update_handle);
	mlxsw_reg_mcda_offset_set(payload, offset);
	mlxsw_reg_mcda_size_set(payload, size);

	for (i = 0; i < size / 4; i++)
		mlxsw_reg_mcda_data_set(payload, i, *(u32 *) &data[i * 4]);
}