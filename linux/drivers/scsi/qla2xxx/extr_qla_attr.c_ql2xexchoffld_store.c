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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int u_ql2xexchoffld; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int FW_MAX_EXCHANGES_CNT ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 TYPE_1__* shost_priv (int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static ssize_t
ql2xexchoffld_store(struct device *dev, struct device_attribute *attr,
    const char *buf, size_t count)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int val = 0;

	if (sscanf(buf, "%d", &val) != 1)
		return -EINVAL;

	if (val > FW_MAX_EXCHANGES_CNT)
		val = FW_MAX_EXCHANGES_CNT;
	else if (val < 0)
		val = 0;

	vha->u_ql2xexchoffld = val;
	return strlen(buf);
}