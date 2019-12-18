#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int current_topology; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int device_flags; int /*<<< orphan*/  loop_state; struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int DFLG_NO_CABLE ; 
#define  ISP_CFG_F 131 
#define  ISP_CFG_FL 130 
#define  ISP_CFG_N 129 
#define  ISP_CFG_NL 128 
 scalar_t__ LOOP_DEAD ; 
 scalar_t__ LOOP_DOWN ; 
 scalar_t__ LOOP_READY ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 scalar_t__ qla2x00_chip_is_down (TYPE_1__*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qla2x00_link_state_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	int len = 0;

	if (atomic_read(&vha->loop_state) == LOOP_DOWN ||
	    atomic_read(&vha->loop_state) == LOOP_DEAD ||
	    vha->device_flags & DFLG_NO_CABLE)
		len = scnprintf(buf, PAGE_SIZE, "Link Down\n");
	else if (atomic_read(&vha->loop_state) != LOOP_READY ||
	    qla2x00_chip_is_down(vha))
		len = scnprintf(buf, PAGE_SIZE, "Unknown Link State\n");
	else {
		len = scnprintf(buf, PAGE_SIZE, "Link Up - ");

		switch (ha->current_topology) {
		case ISP_CFG_NL:
			len += scnprintf(buf + len, PAGE_SIZE-len, "Loop\n");
			break;
		case ISP_CFG_FL:
			len += scnprintf(buf + len, PAGE_SIZE-len, "FL_Port\n");
			break;
		case ISP_CFG_N:
			len += scnprintf(buf + len, PAGE_SIZE-len,
			    "N_Port to N_Port\n");
			break;
		case ISP_CFG_F:
			len += scnprintf(buf + len, PAGE_SIZE-len, "F_Port\n");
			break;
		default:
			len += scnprintf(buf + len, PAGE_SIZE-len, "Loop\n");
			break;
		}
	}
	return len;
}