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
struct adxl34x {int suspended; int /*<<< orphan*/  mutex; scalar_t__ opened; int /*<<< orphan*/  disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  __adxl34x_enable (struct adxl34x*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void adxl34x_resume(struct adxl34x *ac)
{
	mutex_lock(&ac->mutex);

	if (ac->suspended && !ac->disabled && ac->opened)
		__adxl34x_enable(ac);

	ac->suspended = false;

	mutex_unlock(&ac->mutex);
}