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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLXSW_EMAD_OP_TLV_RESPONSE ; 
 char* mlxsw_emad_op_tlv (struct sk_buff const*) ; 
 scalar_t__ mlxsw_emad_op_tlv_r_get (char*) ; 

__attribute__((used)) static bool mlxsw_emad_is_resp(const struct sk_buff *skb)
{
	char *op_tlv;

	op_tlv = mlxsw_emad_op_tlv(skb);
	return (mlxsw_emad_op_tlv_r_get(op_tlv) == MLXSW_EMAD_OP_TLV_RESPONSE);
}