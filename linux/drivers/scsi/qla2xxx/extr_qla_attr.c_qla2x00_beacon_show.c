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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_5__ {TYPE_1__* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_4__ {scalar_t__ beacon_blink_led; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*) ; 
 TYPE_2__* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qla2x00_beacon_show(struct device *dev, struct device_attribute *attr,
		    char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int len = 0;

	if (vha->hw->beacon_blink_led)
		len += scnprintf(buf + len, PAGE_SIZE-len, "Enabled\n");
	else
		len += scnprintf(buf + len, PAGE_SIZE-len, "Disabled\n");
	return len;
}