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
 int __i2c_debugfs_open (struct inode*,struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c1_debugfs_open(struct inode *in, struct file *fp)
{
	return __i2c_debugfs_open(in, fp, 0);
}