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
struct hostaudio_state {int fd; } ;
struct file {int f_mode; struct hostaudio_state* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OPENFLAGS () ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dsp ; 
 int /*<<< orphan*/  hostaudio_mutex ; 
 int /*<<< orphan*/  kernel_param_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_param_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hostaudio_state*) ; 
 struct hostaudio_state* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_set_rw (int /*<<< orphan*/ ,int,int) ; 
 int os_open_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hostaudio_open(struct inode *inode, struct file *file)
{
	struct hostaudio_state *state;
	int r = 0, w = 0;
	int ret;

#ifdef DEBUG
	kernel_param_lock(THIS_MODULE);
	printk(KERN_DEBUG "hostaudio: open called (host: %s)\n", dsp);
	kernel_param_unlock(THIS_MODULE);
#endif

	state = kmalloc(sizeof(struct hostaudio_state), GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;

	if (file->f_mode & FMODE_READ)
		r = 1;
	if (file->f_mode & FMODE_WRITE)
		w = 1;

	kernel_param_lock(THIS_MODULE);
	mutex_lock(&hostaudio_mutex);
	ret = os_open_file(dsp, of_set_rw(OPENFLAGS(), r, w), 0);
	mutex_unlock(&hostaudio_mutex);
	kernel_param_unlock(THIS_MODULE);

	if (ret < 0) {
		kfree(state);
		return ret;
	}
	state->fd = ret;
	file->private_data = state;
	return 0;
}