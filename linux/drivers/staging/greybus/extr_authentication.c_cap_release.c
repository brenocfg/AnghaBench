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
struct gb_cap {int dummy; } ;
struct file {struct gb_cap* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_cap (struct gb_cap*) ; 

__attribute__((used)) static int cap_release(struct inode *inode, struct file *file)
{
	struct gb_cap *cap = file->private_data;

	put_cap(cap);
	return 0;
}