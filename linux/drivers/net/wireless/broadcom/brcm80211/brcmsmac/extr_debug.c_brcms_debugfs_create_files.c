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
struct brcms_pub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_debugfs_add_entry (struct brcms_pub*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_debugfs_hardware_read ; 
 int /*<<< orphan*/  brcms_debugfs_macstat_read ; 

void brcms_debugfs_create_files(struct brcms_pub *drvr)
{
	brcms_debugfs_add_entry(drvr, "hardware", brcms_debugfs_hardware_read);
	brcms_debugfs_add_entry(drvr, "macstat", brcms_debugfs_macstat_read);
}