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
struct TYPE_2__ {scalar_t__ adb_type; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MAC_ADB_II ; 
 TYPE_1__* macintosh_config ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  via ; 
 int /*<<< orphan*/  via1 ; 

__attribute__((used)) static int macii_probe(void)
{
	if (macintosh_config->adb_type != MAC_ADB_II) return -ENODEV;

	via = via1;

	printk("adb: Mac II ADB Driver v1.0 for Unified ADB\n");
	return 0;
}