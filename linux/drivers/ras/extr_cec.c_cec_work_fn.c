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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ce_arr ; 
 int /*<<< orphan*/  ce_mutex ; 
 int /*<<< orphan*/  cec_mod_work (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decay_interval ; 
 int /*<<< orphan*/  do_spring_cleaning (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cec_work_fn(struct work_struct *work)
{
	mutex_lock(&ce_mutex);
	do_spring_cleaning(&ce_arr);
	mutex_unlock(&ce_mutex);

	cec_mod_work(decay_interval);
}