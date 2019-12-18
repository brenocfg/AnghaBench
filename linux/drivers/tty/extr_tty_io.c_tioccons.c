#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {TYPE_1__* f_op; } ;
struct TYPE_2__ {scalar_t__ write; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EBUSY ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct file* get_file (struct file*) ; 
 struct file* redirect ; 
 int /*<<< orphan*/  redirect_lock ; 
 scalar_t__ redirected_tty_write ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tioccons(struct file *file)
{
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	if (file->f_op->write == redirected_tty_write) {
		struct file *f;
		spin_lock(&redirect_lock);
		f = redirect;
		redirect = NULL;
		spin_unlock(&redirect_lock);
		if (f)
			fput(f);
		return 0;
	}
	spin_lock(&redirect_lock);
	if (redirect) {
		spin_unlock(&redirect_lock);
		return -EBUSY;
	}
	redirect = get_file(file);
	spin_unlock(&redirect_lock);
	return 0;
}