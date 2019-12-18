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

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_mcqi_cap_log_mcda_word_size_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mcqi_cap_max_component_size_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mcqi_cap_mcda_max_write_size_get (char*) ; 

__attribute__((used)) static inline void mlxsw_reg_mcqi_unpack(char *payload,
					 u32 *p_cap_max_component_size,
					 u8 *p_cap_log_mcda_word_size,
					 u16 *p_cap_mcda_max_write_size)
{
	*p_cap_max_component_size =
		mlxsw_reg_mcqi_cap_max_component_size_get(payload);
	*p_cap_log_mcda_word_size =
		mlxsw_reg_mcqi_cap_log_mcda_word_size_get(payload);
	*p_cap_mcda_max_write_size =
		mlxsw_reg_mcqi_cap_mcda_max_write_size_get(payload);
}