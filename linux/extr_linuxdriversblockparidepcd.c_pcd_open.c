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
struct pcd_unit {int /*<<< orphan*/  present; } ;
struct cdrom_device_info {struct pcd_unit* handle; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int pcd_open(struct cdrom_device_info *cdi, int purpose)
{
	struct pcd_unit *cd = cdi->handle;
	if (!cd->present)
		return -ENODEV;
	return 0;
}