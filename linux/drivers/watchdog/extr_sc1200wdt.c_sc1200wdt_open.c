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
 int EBUSY ; 
 scalar_t__ MAX_TIMEOUT ; 
 int /*<<< orphan*/  open_flag ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  sc1200wdt_start () ; 
 int stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ timeout ; 

__attribute__((used)) static int sc1200wdt_open(struct inode *inode, struct file *file)
{
	/* allow one at a time */
	if (test_and_set_bit(0, &open_flag))
		return -EBUSY;

	if (timeout > MAX_TIMEOUT)
		timeout = MAX_TIMEOUT;

	sc1200wdt_start();
	pr_info("Watchdog enabled, timeout = %d min(s)", timeout);

	return stream_open(inode, file);
}