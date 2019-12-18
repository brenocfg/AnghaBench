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
struct lock_class_key {int dummy; } ;
struct intel_wakeref_ops {int dummy; } ;
struct intel_wakeref {int /*<<< orphan*/  work; scalar_t__ wakeref; int /*<<< orphan*/  count; int /*<<< orphan*/  mutex; struct intel_wakeref_ops const* ops; struct intel_runtime_pm* rpm; } ;
struct intel_runtime_pm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __intel_wakeref_put_work ; 
 int /*<<< orphan*/  __mutex_init (int /*<<< orphan*/ *,char*,struct lock_class_key*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __intel_wakeref_init(struct intel_wakeref *wf,
			  struct intel_runtime_pm *rpm,
			  const struct intel_wakeref_ops *ops,
			  struct lock_class_key *key)
{
	wf->rpm = rpm;
	wf->ops = ops;

	__mutex_init(&wf->mutex, "wakeref", key);
	atomic_set(&wf->count, 0);
	wf->wakeref = 0;

	INIT_WORK(&wf->work, __intel_wakeref_put_work);
}