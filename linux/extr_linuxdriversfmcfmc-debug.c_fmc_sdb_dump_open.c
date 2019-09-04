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
struct inode {struct fmc_device* i_private; } ;
struct fmc_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fmc_sdb_dump ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct fmc_device*) ; 

__attribute__((used)) static int fmc_sdb_dump_open(struct inode *inode, struct file *file)
{
	struct fmc_device *fmc = inode->i_private;

	return single_open(file, fmc_sdb_dump, fmc);
}