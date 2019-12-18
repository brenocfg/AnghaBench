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
struct TYPE_3__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_PROD ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 TYPE_1__* to_ide_device (struct device*) ; 

__attribute__((used)) static ssize_t model_show(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	ide_drive_t *drive = to_ide_device(dev);
	return sprintf(buf, "%s\n", (char *)&drive->id[ATA_ID_PROD]);
}