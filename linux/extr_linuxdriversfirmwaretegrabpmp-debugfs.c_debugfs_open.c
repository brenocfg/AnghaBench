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
 int /*<<< orphan*/  SZ_128K ; 
 int /*<<< orphan*/  debugfs_show ; 
 int single_open_size (struct file*,int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int debugfs_open(struct inode *inode, struct file *file)
{
	return single_open_size(file, debugfs_show, file, SZ_128K);
}