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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_wdt_stop () ; 
 int /*<<< orphan*/  at91wdt_busy ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 

__attribute__((used)) static int at91_wdt_close(struct inode *inode, struct file *file)
{
	/* Disable the watchdog when file is closed */
	if (!nowayout)
		at91_wdt_stop();

	clear_bit(0, &at91wdt_busy);
	return 0;
}