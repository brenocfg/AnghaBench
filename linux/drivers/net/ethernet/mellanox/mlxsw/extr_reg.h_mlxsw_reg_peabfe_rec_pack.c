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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_peabfe_bf_entry_bank_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_peabfe_bf_entry_index_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_peabfe_bf_entry_state_set (char*,int,int) ; 
 int mlxsw_reg_peabfe_size_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_peabfe_size_set (char*,int) ; 

__attribute__((used)) static inline void mlxsw_reg_peabfe_rec_pack(char *payload, int rec_index,
					     u8 state, u8 bank, u32 bf_index)
{
	u8 num_rec = mlxsw_reg_peabfe_size_get(payload);

	if (rec_index >= num_rec)
		mlxsw_reg_peabfe_size_set(payload, rec_index + 1);
	mlxsw_reg_peabfe_bf_entry_state_set(payload, rec_index, state);
	mlxsw_reg_peabfe_bf_entry_bank_set(payload, rec_index, bank);
	mlxsw_reg_peabfe_bf_entry_index_set(payload, rec_index, bf_index);
}