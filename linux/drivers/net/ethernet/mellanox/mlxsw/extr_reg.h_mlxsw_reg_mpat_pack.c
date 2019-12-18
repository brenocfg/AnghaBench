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
typedef  enum mlxsw_reg_mpat_span_type { ____Placeholder_mlxsw_reg_mpat_span_type } mlxsw_reg_mpat_span_type ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_be_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_e_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_pa_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_qos_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_span_type_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_system_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpat ; 

__attribute__((used)) static inline void mlxsw_reg_mpat_pack(char *payload, u8 pa_id,
				       u16 system_port, bool e,
				       enum mlxsw_reg_mpat_span_type span_type)
{
	MLXSW_REG_ZERO(mpat, payload);
	mlxsw_reg_mpat_pa_id_set(payload, pa_id);
	mlxsw_reg_mpat_system_port_set(payload, system_port);
	mlxsw_reg_mpat_e_set(payload, e);
	mlxsw_reg_mpat_qos_set(payload, 1);
	mlxsw_reg_mpat_be_set(payload, 1);
	mlxsw_reg_mpat_span_type_set(payload, span_type);
}