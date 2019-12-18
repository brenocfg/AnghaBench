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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct scsi_device {int id; int lun; } ;
struct scsi_cmnd {int cmd_len; int /*<<< orphan*/ * cmnd; struct scsi_device* device; } ;
struct esp_target_data {int flags; scalar_t__ nego_goal_period; scalar_t__ nego_goal_offset; scalar_t__ nego_goal_width; int /*<<< orphan*/  starget; scalar_t__ nego_goal_tags; } ;
struct esp_cmd_entry {int flags; scalar_t__* tag; int /*<<< orphan*/  list; struct scsi_cmnd* cmd; } ;
struct esp {int flags; int msg_out_len; scalar_t__ rev; int cmd_bytes_left; int /*<<< orphan*/ * command_block; int /*<<< orphan*/  select_state; scalar_t__* msg_out; int /*<<< orphan*/ * cmd_bytes_ptr; struct esp_cmd_entry* active_cmd; int /*<<< orphan*/  active_cmds; struct esp_target_data* target; } ;

/* Variables and functions */
 scalar_t__ ESP100 ; 
 int /*<<< orphan*/  ESP_BUSID ; 
 int ESP_BUSID_CTR32BIT ; 
 int ESP_BUSID_RESELID ; 
 int ESP_CMD_FLAG_AUTOSENSE ; 
 int ESP_CMD_SA3 ; 
 int ESP_CMD_SELA ; 
 int ESP_CMD_SELAS ; 
 int ESP_DEBUG_SCSICMD ; 
 int ESP_FLAG_RESETTING ; 
 int /*<<< orphan*/  ESP_SELECT_BASIC ; 
 int /*<<< orphan*/  ESP_SELECT_MSGOUT ; 
 int ESP_TGT_BROKEN ; 
 int ESP_TGT_CHECK_NEGO ; 
 int ESP_TGT_DISCONNECT ; 
 int ESP_TGT_NEGO_SYNC ; 
 int ESP_TGT_NEGO_WIDE ; 
 scalar_t__ FASHME ; 
 int /*<<< orphan*/  IDENTIFY (int,int) ; 
 int /*<<< orphan*/  esp_autosense (struct esp*,struct esp_cmd_entry*) ; 
 int esp_debug ; 
 int /*<<< orphan*/  esp_map_dma (struct esp*,struct scsi_cmnd*) ; 
 scalar_t__ esp_need_to_nego_sync (struct esp_target_data*) ; 
 scalar_t__ esp_need_to_nego_wide (struct esp_target_data*) ; 
 int /*<<< orphan*/  esp_save_pointers (struct esp*,struct esp_cmd_entry*) ; 
 int /*<<< orphan*/  esp_send_dma_cmd (struct esp*,int,int,int) ; 
 int /*<<< orphan*/  esp_write8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_write_tgt_config3 (struct esp*,int) ; 
 int /*<<< orphan*/  esp_write_tgt_sync (struct esp*,int) ; 
 struct esp_cmd_entry* find_and_prep_issuable_command (struct esp*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ spi_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ spi_period (int /*<<< orphan*/ ) ; 
 int spi_populate_sync_msg (scalar_t__*,scalar_t__,scalar_t__) ; 
 int spi_populate_width_msg (scalar_t__*,int) ; 
 scalar_t__ spi_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_maybe_execute_command(struct esp *esp)
{
	struct esp_target_data *tp;
	struct scsi_device *dev;
	struct scsi_cmnd *cmd;
	struct esp_cmd_entry *ent;
	bool select_and_stop = false;
	int tgt, lun, i;
	u32 val, start_cmd;
	u8 *p;

	if (esp->active_cmd ||
	    (esp->flags & ESP_FLAG_RESETTING))
		return;

	ent = find_and_prep_issuable_command(esp);
	if (!ent)
		return;

	if (ent->flags & ESP_CMD_FLAG_AUTOSENSE) {
		esp_autosense(esp, ent);
		return;
	}

	cmd = ent->cmd;
	dev = cmd->device;
	tgt = dev->id;
	lun = dev->lun;
	tp = &esp->target[tgt];

	list_move(&ent->list, &esp->active_cmds);

	esp->active_cmd = ent;

	esp_map_dma(esp, cmd);
	esp_save_pointers(esp, ent);

	if (!(cmd->cmd_len == 6 || cmd->cmd_len == 10 || cmd->cmd_len == 12))
		select_and_stop = true;

	p = esp->command_block;

	esp->msg_out_len = 0;
	if (tp->flags & ESP_TGT_CHECK_NEGO) {
		/* Need to negotiate.  If the target is broken
		 * go for synchronous transfers and non-wide.
		 */
		if (tp->flags & ESP_TGT_BROKEN) {
			tp->flags &= ~ESP_TGT_DISCONNECT;
			tp->nego_goal_period = 0;
			tp->nego_goal_offset = 0;
			tp->nego_goal_width = 0;
			tp->nego_goal_tags = 0;
		}

		/* If the settings are not changing, skip this.  */
		if (spi_width(tp->starget) == tp->nego_goal_width &&
		    spi_period(tp->starget) == tp->nego_goal_period &&
		    spi_offset(tp->starget) == tp->nego_goal_offset) {
			tp->flags &= ~ESP_TGT_CHECK_NEGO;
			goto build_identify;
		}

		if (esp->rev == FASHME && esp_need_to_nego_wide(tp)) {
			esp->msg_out_len =
				spi_populate_width_msg(&esp->msg_out[0],
						       (tp->nego_goal_width ?
							1 : 0));
			tp->flags |= ESP_TGT_NEGO_WIDE;
		} else if (esp_need_to_nego_sync(tp)) {
			esp->msg_out_len =
				spi_populate_sync_msg(&esp->msg_out[0],
						      tp->nego_goal_period,
						      tp->nego_goal_offset);
			tp->flags |= ESP_TGT_NEGO_SYNC;
		} else {
			tp->flags &= ~ESP_TGT_CHECK_NEGO;
		}

		/* If there are multiple message bytes, use Select and Stop */
		if (esp->msg_out_len)
			select_and_stop = true;
	}

build_identify:
	*p++ = IDENTIFY(tp->flags & ESP_TGT_DISCONNECT, lun);

	if (ent->tag[0] && esp->rev == ESP100) {
		/* ESP100 lacks select w/atn3 command, use select
		 * and stop instead.
		 */
		select_and_stop = true;
	}

	if (select_and_stop) {
		esp->cmd_bytes_left = cmd->cmd_len;
		esp->cmd_bytes_ptr = &cmd->cmnd[0];

		if (ent->tag[0]) {
			for (i = esp->msg_out_len - 1;
			     i >= 0; i--)
				esp->msg_out[i + 2] = esp->msg_out[i];
			esp->msg_out[0] = ent->tag[0];
			esp->msg_out[1] = ent->tag[1];
			esp->msg_out_len += 2;
		}

		start_cmd = ESP_CMD_SELAS;
		esp->select_state = ESP_SELECT_MSGOUT;
	} else {
		start_cmd = ESP_CMD_SELA;
		if (ent->tag[0]) {
			*p++ = ent->tag[0];
			*p++ = ent->tag[1];

			start_cmd = ESP_CMD_SA3;
		}

		for (i = 0; i < cmd->cmd_len; i++)
			*p++ = cmd->cmnd[i];

		esp->select_state = ESP_SELECT_BASIC;
	}
	val = tgt;
	if (esp->rev == FASHME)
		val |= ESP_BUSID_RESELID | ESP_BUSID_CTR32BIT;
	esp_write8(val, ESP_BUSID);

	esp_write_tgt_sync(esp, tgt);
	esp_write_tgt_config3(esp, tgt);

	val = (p - esp->command_block);

	if (esp_debug & ESP_DEBUG_SCSICMD) {
		printk("ESP: tgt[%d] lun[%d] scsi_cmd [ ", tgt, lun);
		for (i = 0; i < cmd->cmd_len; i++)
			printk("%02x ", cmd->cmnd[i]);
		printk("]\n");
	}

	esp_send_dma_cmd(esp, val, 16, start_cmd);
}