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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_mtbr_rec_max_temp_get (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mtbr_rec_temp_get (char*,int) ; 

__attribute__((used)) static inline void mlxsw_reg_mtbr_temp_unpack(char *payload, int rec_ind,
					      u16 *p_temp, u16 *p_max_temp)
{
	if (p_temp)
		*p_temp = mlxsw_reg_mtbr_rec_temp_get(payload, rec_ind);
	if (p_max_temp)
		*p_max_temp = mlxsw_reg_mtbr_rec_max_temp_get(payload, rec_ind);
}