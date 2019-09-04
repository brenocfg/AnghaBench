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
struct hostmixer_state {int /*<<< orphan*/  fd; } ;
struct file {struct hostmixer_state* private_data; } ;

/* Variables and functions */
 long os_ioctl_generic (int /*<<< orphan*/ ,unsigned int,unsigned long) ; 

__attribute__((used)) static long hostmixer_ioctl_mixdev(struct file *file,
				  unsigned int cmd, unsigned long arg)
{
	struct hostmixer_state *state = file->private_data;

#ifdef DEBUG
	printk(KERN_DEBUG "hostmixer: ioctl called\n");
#endif

	return os_ioctl_generic(state->fd, cmd, arg);
}