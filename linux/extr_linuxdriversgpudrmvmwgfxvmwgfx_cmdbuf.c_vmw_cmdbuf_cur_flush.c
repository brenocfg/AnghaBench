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
struct vmw_cmdbuf_man {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vmw_cmdbuf_cur_flush (struct vmw_cmdbuf_man*) ; 
 int vmw_cmdbuf_cur_lock (struct vmw_cmdbuf_man*,int) ; 
 int /*<<< orphan*/  vmw_cmdbuf_cur_unlock (struct vmw_cmdbuf_man*) ; 

int vmw_cmdbuf_cur_flush(struct vmw_cmdbuf_man *man,
			 bool interruptible)
{
	int ret = vmw_cmdbuf_cur_lock(man, interruptible);

	if (ret)
		return ret;

	__vmw_cmdbuf_cur_flush(man);
	vmw_cmdbuf_cur_unlock(man);

	return 0;
}