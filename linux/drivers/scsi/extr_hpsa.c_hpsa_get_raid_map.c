#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  structure_size; } ;
struct hpsa_scsi_dev_t {TYPE_2__ raid_map; } ;
struct ctlr_info {TYPE_1__* pdev; } ;
struct ErrorInfo {scalar_t__ CommandStatus; } ;
struct CommandList {struct ErrorInfo* err_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CMD_DATA_UNDERRUN ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  HPSA_GET_RAID_MAP ; 
 int /*<<< orphan*/  NO_TIMEOUT ; 
 int /*<<< orphan*/  TYPE_CMD ; 
 struct CommandList* cmd_alloc (struct ctlr_info*) ; 
 int /*<<< orphan*/  cmd_free (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ fill_cmd (struct CommandList*,int /*<<< orphan*/ ,struct ctlr_info*,TYPE_2__*,int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_debug_map_buff (struct ctlr_info*,int,TYPE_2__*) ; 
 int hpsa_scsi_do_simple_cmd_with_retry (struct ctlr_info*,struct CommandList*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_scsi_interpret_error (struct ctlr_info*,struct CommandList*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_get_raid_map(struct ctlr_info *h,
	unsigned char *scsi3addr, struct hpsa_scsi_dev_t *this_device)
{
	int rc = 0;
	struct CommandList *c;
	struct ErrorInfo *ei;

	c = cmd_alloc(h);

	if (fill_cmd(c, HPSA_GET_RAID_MAP, h, &this_device->raid_map,
			sizeof(this_device->raid_map), 0,
			scsi3addr, TYPE_CMD)) {
		dev_warn(&h->pdev->dev, "hpsa_get_raid_map fill_cmd failed\n");
		cmd_free(h, c);
		return -1;
	}
	rc = hpsa_scsi_do_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
			NO_TIMEOUT);
	if (rc)
		goto out;
	ei = c->err_info;
	if (ei->CommandStatus != 0 && ei->CommandStatus != CMD_DATA_UNDERRUN) {
		hpsa_scsi_interpret_error(h, c);
		rc = -1;
		goto out;
	}
	cmd_free(h, c);

	/* @todo in the future, dynamically allocate RAID map memory */
	if (le32_to_cpu(this_device->raid_map.structure_size) >
				sizeof(this_device->raid_map)) {
		dev_warn(&h->pdev->dev, "RAID map size is too large!\n");
		rc = -1;
	}
	hpsa_debug_map_buff(h, rc, &this_device->raid_map);
	return rc;
out:
	cmd_free(h, c);
	return rc;
}