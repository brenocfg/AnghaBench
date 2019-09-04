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
struct hostaudio_state {int /*<<< orphan*/  fd; } ;
struct file {struct hostaudio_state* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hostaudio_state*) ; 
 int /*<<< orphan*/  os_close_file (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hostaudio_release(struct inode *inode, struct file *file)
{
	struct hostaudio_state *state = file->private_data;

#ifdef DEBUG
	printk(KERN_DEBUG "hostaudio: release called\n");
#endif
	os_close_file(state->fd);
	kfree(state);

	return 0;
}