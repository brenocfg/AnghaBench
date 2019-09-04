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
struct loop_device {int (* ioctl ) (struct loop_device*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  LOOP_SET_BLOCK_SIZE 130 
#define  LOOP_SET_CAPACITY 129 
#define  LOOP_SET_DIRECT_IO 128 
 int /*<<< orphan*/  loop_ctl_mutex ; 
 int loop_set_block_size (struct loop_device*,unsigned long) ; 
 int loop_set_capacity (struct loop_device*) ; 
 int loop_set_dio (struct loop_device*,unsigned long) ; 
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct loop_device*,unsigned int,unsigned long) ; 

__attribute__((used)) static int lo_simple_ioctl(struct loop_device *lo, unsigned int cmd,
			   unsigned long arg)
{
	int err;

	err = mutex_lock_killable(&loop_ctl_mutex);
	if (err)
		return err;
	switch (cmd) {
	case LOOP_SET_CAPACITY:
		err = loop_set_capacity(lo);
		break;
	case LOOP_SET_DIRECT_IO:
		err = loop_set_dio(lo, arg);
		break;
	case LOOP_SET_BLOCK_SIZE:
		err = loop_set_block_size(lo, arg);
		break;
	default:
		err = lo->ioctl ? lo->ioctl(lo, cmd, arg) : -EINVAL;
	}
	mutex_unlock(&loop_ctl_mutex);
	return err;
}