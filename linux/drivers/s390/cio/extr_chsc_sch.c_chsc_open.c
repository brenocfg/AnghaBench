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
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chsc_ready_for_use ; 
 int nonseekable_open (struct inode*,struct file*) ; 

__attribute__((used)) static int chsc_open(struct inode *inode, struct file *file)
{
	if (!atomic_dec_and_test(&chsc_ready_for_use)) {
		atomic_inc(&chsc_ready_for_use);
		return -EBUSY;
	}
	return nonseekable_open(inode, file);
}