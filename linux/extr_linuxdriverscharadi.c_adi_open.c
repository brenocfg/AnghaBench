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
struct file {int /*<<< orphan*/  f_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_UNSIGNED_OFFSET ; 

__attribute__((used)) static int adi_open(struct inode *inode, struct file *file)
{
	file->f_mode |= FMODE_UNSIGNED_OFFSET;
	return 0;
}