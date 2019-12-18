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
struct mlxsw_tx_info {int /*<<< orphan*/  local_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_TXHDR_ETH_CTL ; 
 int /*<<< orphan*/  MLXSW_TXHDR_LEN ; 
 int /*<<< orphan*/  MLXSW_TXHDR_PROTO_ETH ; 
 int /*<<< orphan*/  MLXSW_TXHDR_TYPE_CONTROL ; 
 int /*<<< orphan*/  MLXSW_TXHDR_VERSION_1 ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_v1_hdr_control_tclass_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_tx_v1_hdr_ctl_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_v1_hdr_port_mid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_v1_hdr_proto_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_v1_hdr_swid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_v1_hdr_type_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_v1_hdr_version_set (char*,int /*<<< orphan*/ ) ; 
 char* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sib_tx_v1_hdr_construct(struct sk_buff *skb,
			      const struct mlxsw_tx_info *tx_info)
{
	char *txhdr = skb_push(skb, MLXSW_TXHDR_LEN);

	memset(txhdr, 0, MLXSW_TXHDR_LEN);

	mlxsw_tx_v1_hdr_version_set(txhdr, MLXSW_TXHDR_VERSION_1);
	mlxsw_tx_v1_hdr_ctl_set(txhdr, MLXSW_TXHDR_ETH_CTL);
	mlxsw_tx_v1_hdr_proto_set(txhdr, MLXSW_TXHDR_PROTO_ETH);
	mlxsw_tx_v1_hdr_swid_set(txhdr, 0);
	mlxsw_tx_v1_hdr_control_tclass_set(txhdr, 1);
	mlxsw_tx_v1_hdr_port_mid_set(txhdr, tx_info->local_port);
	mlxsw_tx_v1_hdr_type_set(txhdr, MLXSW_TXHDR_TYPE_CONTROL);
}