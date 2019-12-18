#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iwl_rss_config_cmd {int hash_mask; int* indirection_table; int /*<<< orphan*/  secret_key; int /*<<< orphan*/  flags; } ;
struct iwl_mvm {TYPE_1__* trans; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int num_rx_queues; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_RSS_ENABLE ; 
 int /*<<< orphan*/  IWL_RSS_HASH_TYPE_IPV4_PAYLOAD ; 
 int /*<<< orphan*/  IWL_RSS_HASH_TYPE_IPV4_TCP ; 
 int /*<<< orphan*/  IWL_RSS_HASH_TYPE_IPV4_UDP ; 
 int /*<<< orphan*/  IWL_RSS_HASH_TYPE_IPV6_PAYLOAD ; 
 int /*<<< orphan*/  IWL_RSS_HASH_TYPE_IPV6_TCP ; 
 int /*<<< orphan*/  IWL_RSS_HASH_TYPE_IPV6_UDP ; 
 int /*<<< orphan*/  RSS_CONFIG_CMD ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_rss_config_cmd*) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_send_rss_cfg_cmd(struct iwl_mvm *mvm)
{
	int i;
	struct iwl_rss_config_cmd cmd = {
		.flags = cpu_to_le32(IWL_RSS_ENABLE),
		.hash_mask = BIT(IWL_RSS_HASH_TYPE_IPV4_TCP) |
			     BIT(IWL_RSS_HASH_TYPE_IPV4_UDP) |
			     BIT(IWL_RSS_HASH_TYPE_IPV4_PAYLOAD) |
			     BIT(IWL_RSS_HASH_TYPE_IPV6_TCP) |
			     BIT(IWL_RSS_HASH_TYPE_IPV6_UDP) |
			     BIT(IWL_RSS_HASH_TYPE_IPV6_PAYLOAD),
	};

	if (mvm->trans->num_rx_queues == 1)
		return 0;

	/* Do not direct RSS traffic to Q 0 which is our fallback queue */
	for (i = 0; i < ARRAY_SIZE(cmd.indirection_table); i++)
		cmd.indirection_table[i] =
			1 + (i % (mvm->trans->num_rx_queues - 1));
	netdev_rss_key_fill(cmd.secret_key, sizeof(cmd.secret_key));

	return iwl_mvm_send_cmd_pdu(mvm, RSS_CONFIG_CMD, 0, sizeof(cmd), &cmd);
}