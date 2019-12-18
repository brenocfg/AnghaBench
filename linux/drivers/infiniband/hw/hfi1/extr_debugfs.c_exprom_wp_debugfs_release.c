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
struct hfi1_pportdata {int /*<<< orphan*/  dd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprom_in_use ; 
 scalar_t__ exprom_wp_disabled ; 
 int /*<<< orphan*/  exprom_wp_set (int /*<<< orphan*/ ,int) ; 
 struct hfi1_pportdata* private2ppd (struct file*) ; 

__attribute__((used)) static int exprom_wp_debugfs_release(struct inode *in, struct file *fp)
{
	struct hfi1_pportdata *ppd = private2ppd(fp);

	if (exprom_wp_disabled)
		exprom_wp_set(ppd->dd, false);
	clear_bit(0, &exprom_in_use);

	return 0;
}