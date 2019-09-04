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
struct mlxsw_tx_info {int is_emad; int /*<<< orphan*/  local_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_TXHDR_CPU_SIG ; 
 int /*<<< orphan*/  MLXSW_TXHDR_CTCLASS3 ; 
 int /*<<< orphan*/  MLXSW_TXHDR_EMAD ; 
 int /*<<< orphan*/  MLXSW_TXHDR_ETCLASS_5 ; 
 int /*<<< orphan*/  MLXSW_TXHDR_ETCLASS_6 ; 
 int /*<<< orphan*/  MLXSW_TXHDR_ETH_CTL ; 
 int /*<<< orphan*/  MLXSW_TXHDR_LEN ; 
 int /*<<< orphan*/  MLXSW_TXHDR_NOT_EMAD ; 
 int /*<<< orphan*/  MLXSW_TXHDR_PROTO_ETH ; 
 int /*<<< orphan*/  MLXSW_TXHDR_RDQ_EMAD ; 
 int /*<<< orphan*/  MLXSW_TXHDR_RDQ_OTHER ; 
 int /*<<< orphan*/  MLXSW_TXHDR_SIG ; 
 int /*<<< orphan*/  MLXSW_TXHDR_STCLASS_NONE ; 
 int /*<<< orphan*/  MLXSW_TXHDR_TYPE_CONTROL ; 
 int /*<<< orphan*/  MLXSW_TXHDR_VERSION_0 ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_cpu_sig_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_ctclass3_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_ctl_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_emad_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_etclass_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_port_mid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_proto_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_rdq_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_sig_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_stclass_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_swid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_type_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_tx_hdr_version_set (char*,int /*<<< orphan*/ ) ; 
 char* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sx_txhdr_construct(struct sk_buff *skb,
				     const struct mlxsw_tx_info *tx_info)
{
	char *txhdr = skb_push(skb, MLXSW_TXHDR_LEN);
	bool is_emad = tx_info->is_emad;

	memset(txhdr, 0, MLXSW_TXHDR_LEN);

	/* We currently set default values for the egress tclass (QoS). */
	mlxsw_tx_hdr_version_set(txhdr, MLXSW_TXHDR_VERSION_0);
	mlxsw_tx_hdr_ctl_set(txhdr, MLXSW_TXHDR_ETH_CTL);
	mlxsw_tx_hdr_proto_set(txhdr, MLXSW_TXHDR_PROTO_ETH);
	mlxsw_tx_hdr_etclass_set(txhdr, is_emad ? MLXSW_TXHDR_ETCLASS_6 :
						  MLXSW_TXHDR_ETCLASS_5);
	mlxsw_tx_hdr_swid_set(txhdr, 0);
	mlxsw_tx_hdr_port_mid_set(txhdr, tx_info->local_port);
	mlxsw_tx_hdr_ctclass3_set(txhdr, MLXSW_TXHDR_CTCLASS3);
	mlxsw_tx_hdr_rdq_set(txhdr, is_emad ? MLXSW_TXHDR_RDQ_EMAD :
					      MLXSW_TXHDR_RDQ_OTHER);
	mlxsw_tx_hdr_cpu_sig_set(txhdr, MLXSW_TXHDR_CPU_SIG);
	mlxsw_tx_hdr_sig_set(txhdr, MLXSW_TXHDR_SIG);
	mlxsw_tx_hdr_stclass_set(txhdr, MLXSW_TXHDR_STCLASS_NONE);
	mlxsw_tx_hdr_emad_set(txhdr, is_emad ? MLXSW_TXHDR_EMAD :
					       MLXSW_TXHDR_NOT_EMAD);
	mlxsw_tx_hdr_type_set(txhdr, MLXSW_TXHDR_TYPE_CONTROL);
}