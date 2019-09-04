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
struct file {int f_mode; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keypad_available ; 
 scalar_t__ keypad_buflen ; 

__attribute__((used)) static int keypad_open(struct inode *inode, struct file *file)
{
	int ret;

	ret = -EBUSY;
	if (!atomic_dec_and_test(&keypad_available))
		goto fail;	/* open only once at a time */

	ret = -EPERM;
	if (file->f_mode & FMODE_WRITE)	/* device is read-only */
		goto fail;

	keypad_buflen = 0;	/* flush the buffer on opening */
	return 0;
 fail:
	atomic_inc(&keypad_available);
	return ret;
}