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
typedef  enum mlxsw_reg_sfdf_flush_type { ____Placeholder_mlxsw_reg_sfdf_flush_type } mlxsw_reg_sfdf_flush_type ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sfdf_flush_static_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfdf_flush_type_set (char*,int) ; 
 int /*<<< orphan*/  sfdf ; 

__attribute__((used)) static inline void mlxsw_reg_sfdf_pack(char *payload,
				       enum mlxsw_reg_sfdf_flush_type type)
{
	MLXSW_REG_ZERO(sfdf, payload);
	mlxsw_reg_sfdf_flush_type_set(payload, type);
	mlxsw_reg_sfdf_flush_static_set(payload, true);
}