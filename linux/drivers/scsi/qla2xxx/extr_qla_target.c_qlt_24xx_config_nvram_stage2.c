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
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  tgt_node_name; scalar_t__ node_name_set; } ;
struct qla_hw_data {TYPE_1__ tgt; } ;
struct init_cb_24xx {int /*<<< orphan*/  firmware_options_1; int /*<<< orphan*/  node_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_14 ; 
 int /*<<< orphan*/  QLA_TGT_MODE_ENABLED () ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
qlt_24xx_config_nvram_stage2(struct scsi_qla_host *vha,
	struct init_cb_24xx *icb)
{
	struct qla_hw_data *ha = vha->hw;

	if (!QLA_TGT_MODE_ENABLED())
		return;

	if (ha->tgt.node_name_set) {
		memcpy(icb->node_name, ha->tgt.tgt_node_name, WWN_SIZE);
		icb->firmware_options_1 |= cpu_to_le32(BIT_14);
	}
}