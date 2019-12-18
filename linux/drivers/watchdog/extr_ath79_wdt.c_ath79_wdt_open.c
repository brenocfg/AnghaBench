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
 int /*<<< orphan*/  WDT_FLAGS_BUSY ; 
 int /*<<< orphan*/  WDT_FLAGS_EXPECT_CLOSE ; 
 int /*<<< orphan*/  ath79_wdt_enable () ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_flags ; 

__attribute__((used)) static int ath79_wdt_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(WDT_FLAGS_BUSY, &wdt_flags))
		return -EBUSY;

	clear_bit(WDT_FLAGS_EXPECT_CLOSE, &wdt_flags);
	ath79_wdt_enable();

	return stream_open(inode, file);
}