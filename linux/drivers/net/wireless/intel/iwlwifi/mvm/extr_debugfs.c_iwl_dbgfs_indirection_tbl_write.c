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
struct iwl_rss_config_cmd {int hash_mask; int /*<<< orphan*/  secret_key; int /*<<< orphan*/ * indirection_table; int /*<<< orphan*/  flags; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWL_RSS_ENABLE ; 
 int IWL_RSS_HASH_TYPE_IPV4_PAYLOAD ; 
 int IWL_RSS_HASH_TYPE_IPV4_TCP ; 
 int IWL_RSS_HASH_TYPE_IPV4_UDP ; 
 int IWL_RSS_HASH_TYPE_IPV6_PAYLOAD ; 
 int IWL_RSS_HASH_TYPE_IPV6_TCP ; 
 int IWL_RSS_HASH_TYPE_IPV6_UDP ; 
 int /*<<< orphan*/  RSS_CONFIG_CMD ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hex2bin (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ iwl_mvm_firmware_running (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_rss_config_cmd*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_indirection_tbl_write(struct iwl_mvm *mvm,
					       char *buf, size_t count,
					       loff_t *ppos)
{
	struct iwl_rss_config_cmd cmd = {
		.flags = cpu_to_le32(IWL_RSS_ENABLE),
		.hash_mask = IWL_RSS_HASH_TYPE_IPV4_TCP |
			     IWL_RSS_HASH_TYPE_IPV4_UDP |
			     IWL_RSS_HASH_TYPE_IPV4_PAYLOAD |
			     IWL_RSS_HASH_TYPE_IPV6_TCP |
			     IWL_RSS_HASH_TYPE_IPV6_UDP |
			     IWL_RSS_HASH_TYPE_IPV6_PAYLOAD,
	};
	int ret, i, num_repeats, nbytes = count / 2;

	ret = hex2bin(cmd.indirection_table, buf, nbytes);
	if (ret)
		return ret;

	/*
	 * The input is the redirection table, partial or full.
	 * Repeat the pattern if needed.
	 * For example, input of 01020F will be repeated 42 times,
	 * indirecting RSS hash results to queues 1, 2, 15 (skipping
	 * queues 3 - 14).
	 */
	num_repeats = ARRAY_SIZE(cmd.indirection_table) / nbytes;
	for (i = 1; i < num_repeats; i++)
		memcpy(&cmd.indirection_table[i * nbytes],
		       cmd.indirection_table, nbytes);
	/* handle cut in the middle pattern for the last places */
	memcpy(&cmd.indirection_table[i * nbytes], cmd.indirection_table,
	       ARRAY_SIZE(cmd.indirection_table) % nbytes);

	netdev_rss_key_fill(cmd.secret_key, sizeof(cmd.secret_key));

	mutex_lock(&mvm->mutex);
	if (iwl_mvm_firmware_running(mvm))
		ret = iwl_mvm_send_cmd_pdu(mvm, RSS_CONFIG_CMD, 0,
					   sizeof(cmd), &cmd);
	else
		ret = 0;
	mutex_unlock(&mvm->mutex);

	return ret ?: count;
}