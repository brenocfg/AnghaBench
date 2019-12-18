#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct qla_hw_data {scalar_t__ fw_dump_len; scalar_t__ md_dump_size; scalar_t__ md_template_size; int /*<<< orphan*/  fw_dumped; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ IS_P3P_TYPE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_1__* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qla2x00_fw_dump_size_show(struct device *dev, struct device_attribute *attr,
	char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	uint32_t size;

	if (!ha->fw_dumped)
		size = 0;
	else if (IS_P3P_TYPE(ha))
		size = ha->md_template_size + ha->md_dump_size;
	else
		size = ha->fw_dump_len;

	return scnprintf(buf, PAGE_SIZE, "%d\n", size);
}