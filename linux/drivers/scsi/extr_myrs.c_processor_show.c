#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct myrs_hba {struct myrs_ctlr_info* ctlr_info; } ;
struct myrs_ctlr_info {TYPE_1__* cpu; } ;
struct myrs_cpu_type_tbl {scalar_t__ type; char* name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int cpu_count; scalar_t__ cpu_type; char* cpu_name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct myrs_cpu_type_tbl*) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 struct myrs_cpu_type_tbl* myrs_cpu_type_names ; 
 struct myrs_hba* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static ssize_t processor_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct myrs_hba *cs = shost_priv(shost);
	struct myrs_cpu_type_tbl *tbl;
	const char *first_processor = NULL;
	const char *second_processor = NULL;
	struct myrs_ctlr_info *info = cs->ctlr_info;
	ssize_t ret;
	int i;

	if (info->cpu[0].cpu_count) {
		tbl = myrs_cpu_type_names;
		for (i = 0; i < ARRAY_SIZE(myrs_cpu_type_names); i++) {
			if (tbl[i].type == info->cpu[0].cpu_type) {
				first_processor = tbl[i].name;
				break;
			}
		}
	}
	if (info->cpu[1].cpu_count) {
		tbl = myrs_cpu_type_names;
		for (i = 0; i < ARRAY_SIZE(myrs_cpu_type_names); i++) {
			if (tbl[i].type == info->cpu[1].cpu_type) {
				second_processor = tbl[i].name;
				break;
			}
		}
	}
	if (first_processor && second_processor)
		ret = snprintf(buf, 64, "1: %s (%s, %d cpus)\n"
			       "2: %s (%s, %d cpus)\n",
			       info->cpu[0].cpu_name,
			       first_processor, info->cpu[0].cpu_count,
			       info->cpu[1].cpu_name,
			       second_processor, info->cpu[1].cpu_count);
	else if (first_processor && !second_processor)
		ret = snprintf(buf, 64, "1: %s (%s, %d cpus)\n2: absent\n",
			       info->cpu[0].cpu_name,
			       first_processor, info->cpu[0].cpu_count);
	else if (!first_processor && second_processor)
		ret = snprintf(buf, 64, "1: absent\n2: %s (%s, %d cpus)\n",
			       info->cpu[1].cpu_name,
			       second_processor, info->cpu[1].cpu_count);
	else
		ret = snprintf(buf, 64, "1: absent\n2: absent\n");

	return ret;
}