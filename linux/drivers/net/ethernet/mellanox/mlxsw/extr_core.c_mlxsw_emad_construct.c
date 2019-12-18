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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct mlxsw_reg_info {int len; } ;
typedef  enum mlxsw_core_reg_access_type { ____Placeholder_mlxsw_core_reg_access_type } mlxsw_core_reg_access_type ;

/* Variables and functions */
 int MLXSW_EMAD_END_TLV_LEN ; 
 int MLXSW_EMAD_OP_TLV_LEN ; 
 int /*<<< orphan*/  mlxsw_emad_construct_eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  mlxsw_emad_pack_end_tlv (char*) ; 
 int /*<<< orphan*/  mlxsw_emad_pack_op_tlv (char*,struct mlxsw_reg_info const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_emad_pack_reg_tlv (char*,struct mlxsw_reg_info const*,char*) ; 
 char* skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void mlxsw_emad_construct(struct sk_buff *skb,
				 const struct mlxsw_reg_info *reg,
				 char *payload,
				 enum mlxsw_core_reg_access_type type,
				 u64 tid)
{
	char *buf;

	buf = skb_push(skb, MLXSW_EMAD_END_TLV_LEN * sizeof(u32));
	mlxsw_emad_pack_end_tlv(buf);

	buf = skb_push(skb, reg->len + sizeof(u32));
	mlxsw_emad_pack_reg_tlv(buf, reg, payload);

	buf = skb_push(skb, MLXSW_EMAD_OP_TLV_LEN * sizeof(u32));
	mlxsw_emad_pack_op_tlv(buf, reg, type, tid);

	mlxsw_emad_construct_eth_hdr(skb);
}