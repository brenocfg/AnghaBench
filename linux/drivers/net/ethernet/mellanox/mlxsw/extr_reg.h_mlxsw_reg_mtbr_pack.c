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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mtbr_base_sensor_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mtbr_num_rec_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtbr ; 

__attribute__((used)) static inline void mlxsw_reg_mtbr_pack(char *payload, u16 base_sensor_index,
				       u8 num_rec)
{
	MLXSW_REG_ZERO(mtbr, payload);
	mlxsw_reg_mtbr_base_sensor_index_set(payload, base_sensor_index);
	mlxsw_reg_mtbr_num_rec_set(payload, num_rec);
}