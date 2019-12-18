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
struct esp_cmd_priv {scalar_t__ cur_residue; scalar_t__ tot_residue; int /*<<< orphan*/  cur_sg; int /*<<< orphan*/  prv_sg; } ;
struct esp_cmd_entry {int flags; unsigned int sense_ptr; } ;
struct esp {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int ESP_CMD_FLAG_AUTOSENSE ; 
 struct esp_cmd_priv* ESP_CMD_PRIV (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ sg_dma_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void esp_advance_dma(struct esp *esp, struct esp_cmd_entry *ent,
			    struct scsi_cmnd *cmd, unsigned int len)
{
	struct esp_cmd_priv *p = ESP_CMD_PRIV(cmd);

	if (ent->flags & ESP_CMD_FLAG_AUTOSENSE) {
		ent->sense_ptr += len;
		return;
	}

	p->cur_residue -= len;
	p->tot_residue -= len;
	if (p->cur_residue < 0 || p->tot_residue < 0) {
		shost_printk(KERN_ERR, esp->host,
			     "Data transfer overflow.\n");
		shost_printk(KERN_ERR, esp->host,
			     "cur_residue[%d] tot_residue[%d] len[%u]\n",
			     p->cur_residue, p->tot_residue, len);
		p->cur_residue = 0;
		p->tot_residue = 0;
	}
	if (!p->cur_residue && p->tot_residue) {
		p->prv_sg = p->cur_sg;
		p->cur_sg = sg_next(p->cur_sg);
		p->cur_residue = sg_dma_len(p->cur_sg);
	}
}