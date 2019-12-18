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
struct dpu_rm_hw_iter {int dummy; } ;
struct dpu_rm {int /*<<< orphan*/  rm_lock; } ;

/* Variables and functions */
 int _dpu_rm_get_hw_locked (struct dpu_rm*,struct dpu_rm_hw_iter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool dpu_rm_get_hw(struct dpu_rm *rm, struct dpu_rm_hw_iter *i)
{
	bool ret;

	mutex_lock(&rm->rm_lock);
	ret = _dpu_rm_get_hw_locked(rm, i);
	mutex_unlock(&rm->rm_lock);

	return ret;
}