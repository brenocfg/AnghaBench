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
struct mce {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mce_log (struct mce*) ; 
 int /*<<< orphan*/  mce_log_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mce_inject_log(struct mce *m)
{
	mutex_lock(&mce_log_mutex);
	mce_log(m);
	mutex_unlock(&mce_log_mutex);
}