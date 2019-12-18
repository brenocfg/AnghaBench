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
typedef  enum mlxsw_reg_sfd_op { ____Placeholder_mlxsw_reg_sfd_op } mlxsw_reg_sfd_op ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_op_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_record_locator_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfd ; 

__attribute__((used)) static inline void mlxsw_reg_sfd_pack(char *payload, enum mlxsw_reg_sfd_op op,
				      u32 record_locator)
{
	MLXSW_REG_ZERO(sfd, payload);
	mlxsw_reg_sfd_op_set(payload, op);
	mlxsw_reg_sfd_record_locator_set(payload, record_locator);
}