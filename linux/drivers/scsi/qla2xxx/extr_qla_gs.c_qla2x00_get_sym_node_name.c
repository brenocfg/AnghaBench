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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {char* fw_version; } ;
struct qla_hw_data {char* model_number; int fw_major_version; int fw_minor_version; int fw_subminor_version; TYPE_1__ mr; } ;
struct TYPE_5__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ IS_QLAFX00 (struct qla_hw_data*) ; 
 char* qla2x00_version_str ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,size_t,char*,char*,...) ; 

void
qla2x00_get_sym_node_name(scsi_qla_host_t *vha, uint8_t *snn, size_t size)
{
	struct qla_hw_data *ha = vha->hw;

	if (IS_QLAFX00(ha))
		snprintf(snn, size, "%s FW:v%s DVR:v%s", ha->model_number,
		    ha->mr.fw_version, qla2x00_version_str);
	else
		snprintf(snn, size,
		    "%s FW:v%d.%02d.%02d DVR:v%s", ha->model_number,
		    ha->fw_major_version, ha->fw_minor_version,
		    ha->fw_subminor_version, qla2x00_version_str);
}