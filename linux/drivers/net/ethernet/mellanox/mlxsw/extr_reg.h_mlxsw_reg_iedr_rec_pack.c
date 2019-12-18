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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int mlxsw_reg_iedr_num_rec_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_iedr_num_rec_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_iedr_rec_index_start_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_iedr_rec_size_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_iedr_rec_type_set (char*,int,int) ; 

__attribute__((used)) static inline void mlxsw_reg_iedr_rec_pack(char *payload, int rec_index,
					   u8 rec_type, u16 rec_size,
					   u32 rec_index_start)
{
	u8 num_rec = mlxsw_reg_iedr_num_rec_get(payload);

	if (rec_index >= num_rec)
		mlxsw_reg_iedr_num_rec_set(payload, rec_index + 1);
	mlxsw_reg_iedr_rec_type_set(payload, rec_index, rec_type);
	mlxsw_reg_iedr_rec_size_set(payload, rec_index, rec_size);
	mlxsw_reg_iedr_rec_index_start_set(payload, rec_index, rec_index_start);
}