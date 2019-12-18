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
struct TYPE_3__ {int /*<<< orphan*/  host_no; int /*<<< orphan*/  ql2xiniexchg; int /*<<< orphan*/  u_ql2xiniexchg; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
ql2xiniexchg_show(struct device *dev, struct device_attribute *attr,
    char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int len = 0;

	len += scnprintf(buf + len, PAGE_SIZE-len,
		"target exchange: new %d : current: %d\n\n",
		vha->u_ql2xiniexchg, vha->ql2xiniexchg);

	len += scnprintf(buf + len, PAGE_SIZE-len,
	    "Please (re)set operating mode via \"/sys/class/scsi_host/host%ld/qlini_mode\" to load new setting.\n",
	    vha->host_no);

	return len;
}