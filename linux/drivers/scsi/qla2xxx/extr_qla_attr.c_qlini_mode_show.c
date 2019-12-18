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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int qlini_mode; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
#define  QLA2XXX_INI_MODE_DISABLED 131 
#define  QLA2XXX_INI_MODE_DUAL 130 
#define  QLA2XXX_INI_MODE_ENABLED 129 
#define  QLA2XXX_INI_MODE_EXCLUSIVE 128 
 char* QLA2XXX_INI_MODE_STR_DISABLED ; 
 char* QLA2XXX_INI_MODE_STR_DUAL ; 
 char* QLA2XXX_INI_MODE_STR_ENABLED ; 
 char* QLA2XXX_INI_MODE_STR_EXCLUSIVE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*) ; 
 TYPE_1__* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qlini_mode_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int len = 0;

	len += scnprintf(buf + len, PAGE_SIZE-len,
	    "Supported options: enabled | disabled | dual | exclusive\n");

	/* --- */
	len += scnprintf(buf + len, PAGE_SIZE-len, "Current selection: ");

	switch (vha->qlini_mode) {
	case QLA2XXX_INI_MODE_EXCLUSIVE:
		len += scnprintf(buf + len, PAGE_SIZE-len,
		    QLA2XXX_INI_MODE_STR_EXCLUSIVE);
		break;
	case QLA2XXX_INI_MODE_DISABLED:
		len += scnprintf(buf + len, PAGE_SIZE-len,
		    QLA2XXX_INI_MODE_STR_DISABLED);
		break;
	case QLA2XXX_INI_MODE_ENABLED:
		len += scnprintf(buf + len, PAGE_SIZE-len,
		    QLA2XXX_INI_MODE_STR_ENABLED);
		break;
	case QLA2XXX_INI_MODE_DUAL:
		len += scnprintf(buf + len, PAGE_SIZE-len,
		    QLA2XXX_INI_MODE_STR_DUAL);
		break;
	}
	len += scnprintf(buf + len, PAGE_SIZE-len, "\n");

	return len;
}