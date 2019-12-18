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
struct file {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int fixed_size_llseek (struct file*,int,int,int) ; 
 int vcs_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t vcs_lseek(struct file *file, loff_t offset, int orig)
{
	int size;

	console_lock();
	size = vcs_size(file_inode(file));
	console_unlock();
	if (size < 0)
		return size;
	return fixed_size_llseek(file, offset, orig, size);
}