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
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int eur_expect_close ; 
 int /*<<< orphan*/  eurwdt_disable_timer () ; 
 int /*<<< orphan*/  eurwdt_is_open ; 
 int /*<<< orphan*/  eurwdt_ping () ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static int eurwdt_release(struct inode *inode, struct file *file)
{
	if (eur_expect_close == 42)
		eurwdt_disable_timer();
	else {
		pr_crit("Unexpected close, not stopping watchdog!\n");
		eurwdt_ping();
	}
	clear_bit(0, &eurwdt_is_open);
	eur_expect_close = 0;
	return 0;
}