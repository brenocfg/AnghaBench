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
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WDT_FLAGS_OPEN ; 
 int /*<<< orphan*/  WDT_FLAGS_ORPHAN ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geodewdt_ping () ; 
 int stream_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_flags ; 

__attribute__((used)) static int geodewdt_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(WDT_FLAGS_OPEN, &wdt_flags))
		return -EBUSY;

	if (!test_and_clear_bit(WDT_FLAGS_ORPHAN, &wdt_flags))
		__module_get(THIS_MODULE);

	geodewdt_ping();
	return stream_open(inode, file);
}