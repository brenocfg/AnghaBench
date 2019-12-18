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
typedef  scalar_t__ u8 ;
struct cxgbit_wr_wait {int ret; int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 scalar_t__ CPL_ERR_NONE ; 
 int EIO ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,scalar_t__) ; 

__attribute__((used)) static void
cxgbit_wake_up(struct cxgbit_wr_wait *wr_waitp, const char *func, u8 ret)
{
	if (ret == CPL_ERR_NONE)
		wr_waitp->ret = 0;
	else
		wr_waitp->ret = -EIO;

	if (wr_waitp->ret)
		pr_err("%s: err:%u", func, ret);

	complete(&wr_waitp->completion);
}