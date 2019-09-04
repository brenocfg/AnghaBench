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
struct ata_device {scalar_t__ class; int* gscr; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ ATA_DEV_PMP ; 
 int SATA_PMP_GSCR_DWORDS ; 
 scalar_t__ snprintf (char*,int,char*,int,char) ; 
 struct ata_device* transport_class_to_dev (struct device*) ; 

__attribute__((used)) static ssize_t
show_ata_dev_gscr(struct device *dev,
		  struct device_attribute *attr, char *buf)
{
	struct ata_device *ata_dev = transport_class_to_dev(dev);
	int written = 0, i = 0;

	if (ata_dev->class != ATA_DEV_PMP)
		return 0;
	for(i=0;i<SATA_PMP_GSCR_DWORDS;i++)  {
		written += snprintf(buf+written, 20, "%08x%c",
				    ata_dev->gscr[i],
				    ((i+1) & 3) ? ' ' : '\n');
	}
	if (SATA_PMP_GSCR_DWORDS & 3)
		buf[written-1] = '\n';
	return written;
}