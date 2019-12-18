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
struct device {int dummy; } ;
struct Scsi_Host {unsigned short const host_no; } ;

/* Variables and functions */
 struct Scsi_Host* class_to_shost (struct device*) ; 

__attribute__((used)) static int __scsi_host_match(struct device *dev, const void *data)
{
	struct Scsi_Host *p;
	const unsigned short *hostnum = data;

	p = class_to_shost(dev);
	return p->host_no == *hostnum;
}