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
typedef  enum mlxsw_reg_sfd_rec_policy { ____Placeholder_mlxsw_reg_sfd_rec_policy } mlxsw_reg_sfd_rec_policy ;

/* Variables and functions */
 int MLXSW_REG_SFD_REC_POLICY_DYNAMIC_ENTRY_INGRESS ; 
 int MLXSW_REG_SFD_REC_POLICY_DYNAMIC_ENTRY_MLAG ; 

__attribute__((used)) static enum mlxsw_reg_sfd_rec_policy mlxsw_sp_sfd_rec_policy(bool dynamic)
{
	return dynamic ? MLXSW_REG_SFD_REC_POLICY_DYNAMIC_ENTRY_INGRESS :
			 MLXSW_REG_SFD_REC_POLICY_DYNAMIC_ENTRY_MLAG;
}