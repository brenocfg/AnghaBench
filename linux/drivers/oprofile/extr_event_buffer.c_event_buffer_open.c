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
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  __clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_opened ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcookie_register () ; 
 int /*<<< orphan*/  dcookie_unregister (int /*<<< orphan*/ ) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int oprofile_setup () ; 
 scalar_t__ test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int event_buffer_open(struct inode *inode, struct file *file)
{
	int err = -EPERM;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	if (test_and_set_bit_lock(0, &buffer_opened))
		return -EBUSY;

	/* Register as a user of dcookies
	 * to ensure they persist for the lifetime of
	 * the open event file
	 */
	err = -EINVAL;
	file->private_data = dcookie_register();
	if (!file->private_data)
		goto out;

	if ((err = oprofile_setup()))
		goto fail;

	/* NB: the actual start happens from userspace
	 * echo 1 >/dev/oprofile/enable
	 */

	return nonseekable_open(inode, file);

fail:
	dcookie_unregister(file->private_data);
out:
	__clear_bit_unlock(0, &buffer_opened);
	return err;
}