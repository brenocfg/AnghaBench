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

/* Variables and functions */
 int /*<<< orphan*/  bL_switcher_activation_lock ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void bL_switcher_put_enabled(void)
{
	mutex_unlock(&bL_switcher_activation_lock);
}