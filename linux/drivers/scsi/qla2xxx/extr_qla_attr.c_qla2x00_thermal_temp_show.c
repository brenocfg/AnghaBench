#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_10__ {TYPE_2__* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_8__ {scalar_t__ eeh_busy; } ;
struct TYPE_9__ {int /*<<< orphan*/  optrom_mutex; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_3__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 scalar_t__ qla2x00_chip_is_down (TYPE_3__*) ; 
 int qla2x00_get_thermal_temp (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qla2x00_thermal_temp_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	uint16_t temp = 0;
	int rc;

	mutex_lock(&vha->hw->optrom_mutex);
	if (qla2x00_chip_is_down(vha)) {
		mutex_unlock(&vha->hw->optrom_mutex);
		ql_log(ql_log_warn, vha, 0x70dc, "ISP reset active.\n");
		goto done;
	}

	if (vha->hw->flags.eeh_busy) {
		mutex_unlock(&vha->hw->optrom_mutex);
		ql_log(ql_log_warn, vha, 0x70dd, "PCI EEH busy.\n");
		goto done;
	}

	rc = qla2x00_get_thermal_temp(vha, &temp);
	mutex_unlock(&vha->hw->optrom_mutex);
	if (rc == QLA_SUCCESS)
		return scnprintf(buf, PAGE_SIZE, "%d\n", temp);

done:
	return scnprintf(buf, PAGE_SIZE, "\n");
}