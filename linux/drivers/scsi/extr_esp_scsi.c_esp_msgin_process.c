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
typedef  int u8 ;
struct esp_cmd_priv {int cur_residue; int /*<<< orphan*/  tot_residue; int /*<<< orphan*/  prv_sg; int /*<<< orphan*/  cur_sg; } ;
struct esp_cmd_entry {int message; int /*<<< orphan*/  cmd; } ;
struct esp {int* msg_in; int msg_in_len; int* msg_out; int msg_out_len; int /*<<< orphan*/  flags; struct esp_cmd_entry* active_cmd; int /*<<< orphan*/  host; } ;

/* Variables and functions */
#define  COMMAND_COMPLETE 135 
#define  DISCONNECT 134 
 struct esp_cmd_priv* ESP_CMD_PRIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_CMD_SATN ; 
 int /*<<< orphan*/  ESP_EVENT_FREE_BUS ; 
 int /*<<< orphan*/  ESP_FLAG_QUICKIRQ_CHECK ; 
#define  EXTENDED_MESSAGE 133 
#define  IGNORE_WIDE_RESIDUE 132 
 int /*<<< orphan*/  KERN_INFO ; 
#define  MESSAGE_REJECT 131 
#define  NOP 130 
#define  RESTORE_POINTERS 129 
#define  SAVE_POINTERS 128 
 int /*<<< orphan*/  esp_event (struct esp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_msgin_extended (struct esp*) ; 
 int /*<<< orphan*/  esp_msgin_reject (struct esp*) ; 
 int /*<<< orphan*/  esp_restore_pointers (struct esp*,struct esp_cmd_entry*) ; 
 int /*<<< orphan*/  esp_save_pointers (struct esp*,struct esp_cmd_entry*) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int /*<<< orphan*/ ) ; 
 int sg_dma_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int esp_msgin_process(struct esp *esp)
{
	u8 msg0 = esp->msg_in[0];
	int len = esp->msg_in_len;

	if (msg0 & 0x80) {
		/* Identify */
		shost_printk(KERN_INFO, esp->host,
			     "Unexpected msgin identify\n");
		return 0;
	}

	switch (msg0) {
	case EXTENDED_MESSAGE:
		if (len == 1)
			return 1;
		if (len < esp->msg_in[1] + 2)
			return 1;
		esp_msgin_extended(esp);
		return 0;

	case IGNORE_WIDE_RESIDUE: {
		struct esp_cmd_entry *ent;
		struct esp_cmd_priv *spriv;
		if (len == 1)
			return 1;

		if (esp->msg_in[1] != 1)
			goto do_reject;

		ent = esp->active_cmd;
		spriv = ESP_CMD_PRIV(ent->cmd);

		if (spriv->cur_residue == sg_dma_len(spriv->cur_sg)) {
			spriv->cur_sg = spriv->prv_sg;
			spriv->cur_residue = 1;
		} else
			spriv->cur_residue++;
		spriv->tot_residue++;
		return 0;
	}
	case NOP:
		return 0;
	case RESTORE_POINTERS:
		esp_restore_pointers(esp, esp->active_cmd);
		return 0;
	case SAVE_POINTERS:
		esp_save_pointers(esp, esp->active_cmd);
		return 0;

	case COMMAND_COMPLETE:
	case DISCONNECT: {
		struct esp_cmd_entry *ent = esp->active_cmd;

		ent->message = msg0;
		esp_event(esp, ESP_EVENT_FREE_BUS);
		esp->flags |= ESP_FLAG_QUICKIRQ_CHECK;
		return 0;
	}
	case MESSAGE_REJECT:
		esp_msgin_reject(esp);
		return 0;

	default:
	do_reject:
		esp->msg_out[0] = MESSAGE_REJECT;
		esp->msg_out_len = 1;
		scsi_esp_cmd(esp, ESP_CMD_SATN);
		return 0;
	}
}