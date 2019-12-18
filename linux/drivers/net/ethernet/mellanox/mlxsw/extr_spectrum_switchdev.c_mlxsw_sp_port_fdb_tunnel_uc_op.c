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
union mlxsw_sp_l3addr {int /*<<< orphan*/  addr4; } ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;
typedef  enum mlxsw_reg_sfd_uc_tunnel_protocol { ____Placeholder_mlxsw_reg_sfd_uc_tunnel_protocol } mlxsw_reg_sfd_uc_tunnel_protocol ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_SFD_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_SFD_REC_ACTION_NOP ; 
 int MLXSW_REG_SFD_UC_TUNNEL_PROTOCOL_IPV4 ; 
#define  MLXSW_SP_L3_PROTO_IPV4 129 
#define  MLXSW_SP_L3_PROTO_IPV6 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_reg_sfd_num_rec_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_uc_tunnel_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_sfd_op (int) ; 
 int /*<<< orphan*/  mlxsw_sp_sfd_rec_policy (int) ; 
 int /*<<< orphan*/  sfd ; 

__attribute__((used)) static int mlxsw_sp_port_fdb_tunnel_uc_op(struct mlxsw_sp *mlxsw_sp,
					  const char *mac, u16 fid,
					  enum mlxsw_sp_l3proto proto,
					  const union mlxsw_sp_l3addr *addr,
					  bool adding, bool dynamic)
{
	enum mlxsw_reg_sfd_uc_tunnel_protocol sfd_proto;
	char *sfd_pl;
	u8 num_rec;
	u32 uip;
	int err;

	switch (proto) {
	case MLXSW_SP_L3_PROTO_IPV4:
		uip = be32_to_cpu(addr->addr4);
		sfd_proto = MLXSW_REG_SFD_UC_TUNNEL_PROTOCOL_IPV4;
		break;
	case MLXSW_SP_L3_PROTO_IPV6: /* fall through */
	default:
		WARN_ON(1);
		return -EOPNOTSUPP;
	}

	sfd_pl = kmalloc(MLXSW_REG_SFD_LEN, GFP_KERNEL);
	if (!sfd_pl)
		return -ENOMEM;

	mlxsw_reg_sfd_pack(sfd_pl, mlxsw_sp_sfd_op(adding), 0);
	mlxsw_reg_sfd_uc_tunnel_pack(sfd_pl, 0,
				     mlxsw_sp_sfd_rec_policy(dynamic), mac, fid,
				     MLXSW_REG_SFD_REC_ACTION_NOP, uip,
				     sfd_proto);
	num_rec = mlxsw_reg_sfd_num_rec_get(sfd_pl);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sfd), sfd_pl);
	if (err)
		goto out;

	if (num_rec != mlxsw_reg_sfd_num_rec_get(sfd_pl))
		err = -EBUSY;

out:
	kfree(sfd_pl);
	return err;
}