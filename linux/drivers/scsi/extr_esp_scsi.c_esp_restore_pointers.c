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
struct scsi_cmnd {int dummy; } ;
struct esp_cmd_priv {int /*<<< orphan*/  tot_residue; int /*<<< orphan*/  cur_sg; int /*<<< orphan*/  prv_sg; int /*<<< orphan*/  cur_residue; } ;
struct esp_cmd_entry {int flags; int /*<<< orphan*/  saved_tot_residue; int /*<<< orphan*/  saved_cur_sg; int /*<<< orphan*/  saved_prv_sg; int /*<<< orphan*/  saved_cur_residue; int /*<<< orphan*/  saved_sense_ptr; int /*<<< orphan*/  sense_ptr; struct scsi_cmnd* cmd; } ;
struct esp {int dummy; } ;

/* Variables and functions */
 int ESP_CMD_FLAG_AUTOSENSE ; 
 struct esp_cmd_priv* ESP_CMD_PRIV (struct scsi_cmnd*) ; 

__attribute__((used)) static void esp_restore_pointers(struct esp *esp, struct esp_cmd_entry *ent)
{
	struct scsi_cmnd *cmd = ent->cmd;
	struct esp_cmd_priv *spriv = ESP_CMD_PRIV(cmd);

	if (ent->flags & ESP_CMD_FLAG_AUTOSENSE) {
		ent->sense_ptr = ent->saved_sense_ptr;
		return;
	}
	spriv->cur_residue = ent->saved_cur_residue;
	spriv->prv_sg = ent->saved_prv_sg;
	spriv->cur_sg = ent->saved_cur_sg;
	spriv->tot_residue = ent->saved_tot_residue;
}