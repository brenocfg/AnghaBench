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
struct TYPE_4__ {TYPE_1__* disk; } ;
struct TYPE_3__ {int first_minor; int minors; int /*<<< orphan*/  disk_name; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDROM_DEV_NAME ; 
 TYPE_2__ gd ; 
 int /*<<< orphan*/  gdrom_major ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void probe_gdrom_setupdisk(void)
{
	gd.disk->major = gdrom_major;
	gd.disk->first_minor = 1;
	gd.disk->minors = 1;
	strcpy(gd.disk->disk_name, GDROM_DEV_NAME);
}