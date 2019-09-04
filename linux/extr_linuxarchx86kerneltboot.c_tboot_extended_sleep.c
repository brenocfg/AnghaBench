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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  tboot_enabled () ; 

__attribute__((used)) static int tboot_extended_sleep(u8 sleep_state, u32 val_a, u32 val_b)
{
	if (!tboot_enabled())
		return 0;

	pr_warning("tboot is not able to suspend on platforms with reduced hardware sleep (ACPIv5)");
	return -ENODEV;
}