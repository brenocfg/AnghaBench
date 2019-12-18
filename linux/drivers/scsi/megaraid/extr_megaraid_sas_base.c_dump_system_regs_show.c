#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct megasas_instance {int /*<<< orphan*/  reg_set; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  megasas_dump_sys_regs (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t
dump_system_regs_show(struct device *cdev,
			       struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct megasas_instance *instance =
			(struct megasas_instance *)shost->hostdata;

	return megasas_dump_sys_regs(instance->reg_set, buf);
}