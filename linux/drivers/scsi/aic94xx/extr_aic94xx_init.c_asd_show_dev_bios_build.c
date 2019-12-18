#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int bld; } ;
struct TYPE_4__ {TYPE_1__ bios; } ;
struct asd_ha_struct {TYPE_2__ hw_prof; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct asd_ha_struct* dev_to_asd_ha (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t asd_show_dev_bios_build(struct device *dev,
				       struct device_attribute *attr,char *buf)
{
	struct asd_ha_struct *asd_ha = dev_to_asd_ha(dev);
	return snprintf(buf, PAGE_SIZE, "%d\n", asd_ha->hw_prof.bios.bld);
}