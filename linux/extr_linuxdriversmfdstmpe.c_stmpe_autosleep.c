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
struct stmpe {int /*<<< orphan*/  lock; TYPE_1__* variant; } ;
struct TYPE_2__ {int (* enable_autosleep ) (struct stmpe*,int) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct stmpe*,int) ; 

__attribute__((used)) static int stmpe_autosleep(struct stmpe *stmpe, int autosleep_timeout)
{
	int ret;

	if (!stmpe->variant->enable_autosleep)
		return -ENOSYS;

	mutex_lock(&stmpe->lock);
	ret = stmpe->variant->enable_autosleep(stmpe, autosleep_timeout);
	mutex_unlock(&stmpe->lock);

	return ret;
}