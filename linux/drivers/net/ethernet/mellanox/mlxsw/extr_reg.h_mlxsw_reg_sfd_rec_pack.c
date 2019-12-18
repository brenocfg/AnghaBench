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
typedef  int u8 ;
typedef  enum mlxsw_reg_sfd_rec_type { ____Placeholder_mlxsw_reg_sfd_rec_type } mlxsw_reg_sfd_rec_type ;
typedef  enum mlxsw_reg_sfd_rec_action { ____Placeholder_mlxsw_reg_sfd_rec_action } mlxsw_reg_sfd_rec_action ;

/* Variables and functions */
 int mlxsw_reg_sfd_num_rec_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_num_rec_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_rec_action_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_rec_mac_memcpy_to (char*,int,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_rec_swid_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_rec_type_set (char*,int,int) ; 

__attribute__((used)) static inline void mlxsw_reg_sfd_rec_pack(char *payload, int rec_index,
					  enum mlxsw_reg_sfd_rec_type rec_type,
					  const char *mac,
					  enum mlxsw_reg_sfd_rec_action action)
{
	u8 num_rec = mlxsw_reg_sfd_num_rec_get(payload);

	if (rec_index >= num_rec)
		mlxsw_reg_sfd_num_rec_set(payload, rec_index + 1);
	mlxsw_reg_sfd_rec_swid_set(payload, rec_index, 0);
	mlxsw_reg_sfd_rec_type_set(payload, rec_index, rec_type);
	mlxsw_reg_sfd_rec_mac_memcpy_to(payload, rec_index, mac);
	mlxsw_reg_sfd_rec_action_set(payload, rec_index, action);
}