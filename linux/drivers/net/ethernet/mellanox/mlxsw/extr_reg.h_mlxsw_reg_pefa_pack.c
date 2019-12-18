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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_pefa_ca_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_pefa_flex_action_set_memcpy_to (char*,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_pefa_index_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pefa ; 

__attribute__((used)) static inline void mlxsw_reg_pefa_pack(char *payload, u32 index, bool ca,
				       const char *flex_action_set)
{
	MLXSW_REG_ZERO(pefa, payload);
	mlxsw_reg_pefa_index_set(payload, index);
	mlxsw_reg_pefa_ca_set(payload, ca);
	if (flex_action_set)
		mlxsw_reg_pefa_flex_action_set_memcpy_to(payload,
							 flex_action_set);
}