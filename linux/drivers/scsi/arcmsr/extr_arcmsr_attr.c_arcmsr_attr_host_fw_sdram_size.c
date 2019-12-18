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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct AdapterControlBlock {int firm_sdram_size; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t
arcmsr_attr_host_fw_sdram_size(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *host = class_to_shost(dev);
	struct AdapterControlBlock *acb =
		(struct AdapterControlBlock *) host->hostdata;

	return snprintf(buf, PAGE_SIZE,
			"%4d\n",
			acb->firm_sdram_size);
}