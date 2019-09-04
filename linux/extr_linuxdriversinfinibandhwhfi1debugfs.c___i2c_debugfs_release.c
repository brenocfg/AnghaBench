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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct hfi1_pportdata {int /*<<< orphan*/  dd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  i2c_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct hfi1_pportdata* private2ppd (struct file*) ; 
 int /*<<< orphan*/  release_chip_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __i2c_debugfs_release(struct inode *in, struct file *fp, u32 target)
{
	struct hfi1_pportdata *ppd;

	ppd = private2ppd(fp);

	release_chip_resource(ppd->dd, i2c_target(target));
	module_put(THIS_MODULE);

	return 0;
}