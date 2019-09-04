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
 int MLXSW_REG_SPVMLR_REC_MAX_COUNT ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_reg_spvmlr_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_spvmlr_num_rec_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_spvmlr_rec_learn_enable_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_spvmlr_rec_vid_set (char*,int,int) ; 
 int /*<<< orphan*/  spvmlr ; 

__attribute__((used)) static inline void mlxsw_reg_spvmlr_pack(char *payload, u8 local_port,
					 u16 vid_begin, u16 vid_end,
					 bool learn_enable)
{
	int num_rec = vid_end - vid_begin + 1;
	int i;

	WARN_ON(num_rec < 1 || num_rec > MLXSW_REG_SPVMLR_REC_MAX_COUNT);

	MLXSW_REG_ZERO(spvmlr, payload);
	mlxsw_reg_spvmlr_local_port_set(payload, local_port);
	mlxsw_reg_spvmlr_num_rec_set(payload, num_rec);

	for (i = 0; i < num_rec; i++) {
		mlxsw_reg_spvmlr_rec_learn_enable_set(payload, i, learn_enable);
		mlxsw_reg_spvmlr_rec_vid_set(payload, i, vid_begin + i);
	}
}