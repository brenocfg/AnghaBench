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
struct scsi_device {struct esp_lun_data* hostdata; } ;
struct esp_target_data {int /*<<< orphan*/  starget; } ;
struct esp_lun_data {struct esp_cmd_entry* non_tagged_cmd; } ;
struct esp_cmd_entry {int dummy; } ;
struct esp {scalar_t__ rev; int* fifo; int scsi_id_mask; int /*<<< orphan*/  flags; struct esp_cmd_entry* active_cmd; int /*<<< orphan*/  host; struct esp_target_data* target; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct esp_cmd_entry*) ; 
 scalar_t__ ESP100 ; 
 int /*<<< orphan*/  ESP_BUSID ; 
 int ESP_BUSID_CTR32BIT ; 
 int ESP_BUSID_RESELID ; 
 int /*<<< orphan*/  ESP_CMD_FLUSH ; 
 int /*<<< orphan*/  ESP_CMD_MOK ; 
 int /*<<< orphan*/  ESP_CMD_NULL ; 
 int /*<<< orphan*/  ESP_EVENT_CHECK_PHASE ; 
 int /*<<< orphan*/  ESP_FDATA ; 
 int /*<<< orphan*/  ESP_FLAG_QUICKIRQ_CHECK ; 
 int /*<<< orphan*/  ESP_INTRPT ; 
 int ESP_INTR_SR ; 
 scalar_t__ FASHME ; 
 int /*<<< orphan*/  KERN_ERR ; 
 struct scsi_device* __scsi_device_lookup_by_target (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_event (struct esp*,int /*<<< orphan*/ ) ; 
 int esp_read8 (int /*<<< orphan*/ ) ; 
 struct esp_cmd_entry* esp_reconnect_with_tag (struct esp*,struct esp_lun_data*) ; 
 int /*<<< orphan*/  esp_restore_pointers (struct esp*,struct esp_cmd_entry*) ; 
 int /*<<< orphan*/  esp_schedule_reset (struct esp*) ; 
 int /*<<< orphan*/  esp_write8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_write_tgt_config3 (struct esp*,int) ; 
 int /*<<< orphan*/  esp_write_tgt_sync (struct esp*,int) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int esp_reconnect(struct esp *esp)
{
	struct esp_cmd_entry *ent;
	struct esp_target_data *tp;
	struct esp_lun_data *lp;
	struct scsi_device *dev;
	int target, lun;

	BUG_ON(esp->active_cmd);
	if (esp->rev == FASHME) {
		/* FASHME puts the target and lun numbers directly
		 * into the fifo.
		 */
		target = esp->fifo[0];
		lun = esp->fifo[1] & 0x7;
	} else {
		u8 bits = esp_read8(ESP_FDATA);

		/* Older chips put the lun directly into the fifo, but
		 * the target is given as a sample of the arbitration
		 * lines on the bus at reselection time.  So we should
		 * see the ID of the ESP and the one reconnecting target
		 * set in the bitmap.
		 */
		if (!(bits & esp->scsi_id_mask))
			goto do_reset;
		bits &= ~esp->scsi_id_mask;
		if (!bits || (bits & (bits - 1)))
			goto do_reset;

		target = ffs(bits) - 1;
		lun = (esp_read8(ESP_FDATA) & 0x7);

		scsi_esp_cmd(esp, ESP_CMD_FLUSH);
		if (esp->rev == ESP100) {
			u8 ireg = esp_read8(ESP_INTRPT);
			/* This chip has a bug during reselection that can
			 * cause a spurious illegal-command interrupt, which
			 * we simply ACK here.  Another possibility is a bus
			 * reset so we must check for that.
			 */
			if (ireg & ESP_INTR_SR)
				goto do_reset;
		}
		scsi_esp_cmd(esp, ESP_CMD_NULL);
	}

	esp_write_tgt_sync(esp, target);
	esp_write_tgt_config3(esp, target);

	scsi_esp_cmd(esp, ESP_CMD_MOK);

	if (esp->rev == FASHME)
		esp_write8(target | ESP_BUSID_RESELID | ESP_BUSID_CTR32BIT,
			   ESP_BUSID);

	tp = &esp->target[target];
	dev = __scsi_device_lookup_by_target(tp->starget, lun);
	if (!dev) {
		shost_printk(KERN_ERR, esp->host,
			     "Reconnect, no lp tgt[%u] lun[%u]\n",
			     target, lun);
		goto do_reset;
	}
	lp = dev->hostdata;

	ent = lp->non_tagged_cmd;
	if (!ent) {
		ent = esp_reconnect_with_tag(esp, lp);
		if (!ent)
			goto do_reset;
	}

	esp->active_cmd = ent;

	esp_event(esp, ESP_EVENT_CHECK_PHASE);
	esp_restore_pointers(esp, ent);
	esp->flags |= ESP_FLAG_QUICKIRQ_CHECK;
	return 1;

do_reset:
	esp_schedule_reset(esp);
	return 0;
}