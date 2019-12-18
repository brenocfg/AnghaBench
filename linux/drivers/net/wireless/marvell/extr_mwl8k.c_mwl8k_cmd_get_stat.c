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
struct TYPE_2__ {void* length; void* code; } ;
struct mwl8k_cmd_get_stat {int /*<<< orphan*/ * stats; TYPE_1__ header; } ;
struct ieee80211_low_level_stats {void* dot11RTSSuccessCount; void* dot11FCSErrorCount; void* dot11RTSFailureCount; void* dot11ACKFailureCount; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_GET_STAT ; 
 size_t MWL8K_STAT_ACK_FAILURE ; 
 size_t MWL8K_STAT_FCS_ERROR ; 
 size_t MWL8K_STAT_RTS_FAILURE ; 
 size_t MWL8K_STAT_RTS_SUCCESS ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_get_stat*) ; 
 struct mwl8k_cmd_get_stat* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_1__*) ; 

__attribute__((used)) static int mwl8k_cmd_get_stat(struct ieee80211_hw *hw,
			      struct ieee80211_low_level_stats *stats)
{
	struct mwl8k_cmd_get_stat *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_GET_STAT);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));

	rc = mwl8k_post_cmd(hw, &cmd->header);
	if (!rc) {
		stats->dot11ACKFailureCount =
			le32_to_cpu(cmd->stats[MWL8K_STAT_ACK_FAILURE]);
		stats->dot11RTSFailureCount =
			le32_to_cpu(cmd->stats[MWL8K_STAT_RTS_FAILURE]);
		stats->dot11FCSErrorCount =
			le32_to_cpu(cmd->stats[MWL8K_STAT_FCS_ERROR]);
		stats->dot11RTSSuccessCount =
			le32_to_cpu(cmd->stats[MWL8K_STAT_RTS_SUCCESS]);
	}
	kfree(cmd);

	return rc;
}