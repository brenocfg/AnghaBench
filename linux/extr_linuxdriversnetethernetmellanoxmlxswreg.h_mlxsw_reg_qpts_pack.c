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
typedef  enum mlxsw_reg_qpts_trust_state { ____Placeholder_mlxsw_reg_qpts_trust_state } mlxsw_reg_qpts_trust_state ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_qpts_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qpts_trust_state_set (char*,int) ; 
 int /*<<< orphan*/  qpts ; 

__attribute__((used)) static inline void mlxsw_reg_qpts_pack(char *payload, u8 local_port,
				       enum mlxsw_reg_qpts_trust_state ts)
{
	MLXSW_REG_ZERO(qpts, payload);

	mlxsw_reg_qpts_local_port_set(payload, local_port);
	mlxsw_reg_qpts_trust_state_set(payload, ts);
}