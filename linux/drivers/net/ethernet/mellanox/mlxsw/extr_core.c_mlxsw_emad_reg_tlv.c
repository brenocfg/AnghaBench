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
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ MLXSW_EMAD_ETH_HDR_LEN ; 
 int MLXSW_EMAD_OP_TLV_LEN ; 

__attribute__((used)) static char *mlxsw_emad_reg_tlv(const struct sk_buff *skb)
{
	return ((char *) (skb->data + MLXSW_EMAD_ETH_HDR_LEN +
				      MLXSW_EMAD_OP_TLV_LEN * sizeof(u32)));
}