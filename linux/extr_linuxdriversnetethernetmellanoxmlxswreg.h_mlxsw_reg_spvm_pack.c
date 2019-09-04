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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_spvm_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_spvm_num_rec_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_spvm_rec_e_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_spvm_rec_i_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_spvm_rec_u_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_spvm_rec_vid_set (char*,int,int) ; 
 int /*<<< orphan*/  spvm ; 

__attribute__((used)) static inline void mlxsw_reg_spvm_pack(char *payload, u8 local_port,
				       u16 vid_begin, u16 vid_end,
				       bool is_member, bool untagged)
{
	int size = vid_end - vid_begin + 1;
	int i;

	MLXSW_REG_ZERO(spvm, payload);
	mlxsw_reg_spvm_local_port_set(payload, local_port);
	mlxsw_reg_spvm_num_rec_set(payload, size);

	for (i = 0; i < size; i++) {
		mlxsw_reg_spvm_rec_i_set(payload, i, is_member);
		mlxsw_reg_spvm_rec_e_set(payload, i, is_member);
		mlxsw_reg_spvm_rec_u_set(payload, i, untagged);
		mlxsw_reg_spvm_rec_vid_set(payload, i, vid_begin + i);
	}
}