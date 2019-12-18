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
typedef  enum mlxsw_reg_sfd_rec_action { ____Placeholder_mlxsw_reg_sfd_rec_action } mlxsw_reg_sfd_rec_action ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_SFD_REC_TYPE_MULTICAST ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_mc_fid_vid_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_mc_mid_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_mc_pgi_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_rec_pack (char*,int,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static inline void
mlxsw_reg_sfd_mc_pack(char *payload, int rec_index,
		      const char *mac, u16 fid_vid,
		      enum mlxsw_reg_sfd_rec_action action, u16 mid)
{
	mlxsw_reg_sfd_rec_pack(payload, rec_index,
			       MLXSW_REG_SFD_REC_TYPE_MULTICAST, mac, action);
	mlxsw_reg_sfd_mc_pgi_set(payload, rec_index, 0x1FFF);
	mlxsw_reg_sfd_mc_fid_vid_set(payload, rec_index, fid_vid);
	mlxsw_reg_sfd_mc_mid_set(payload, rec_index, mid);
}