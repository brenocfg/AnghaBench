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
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_lock ; 
 int /*<<< orphan*/ * prepare_owner ; 
 int prepare_refcnt ; 

__attribute__((used)) static void clk_prepare_lock(void)
{
	if (!mutex_trylock(&prepare_lock)) {
		if (prepare_owner == current) {
			prepare_refcnt++;
			return;
		}
		mutex_lock(&prepare_lock);
	}
	WARN_ON_ONCE(prepare_owner != NULL);
	WARN_ON_ONCE(prepare_refcnt != 0);
	prepare_owner = current;
	prepare_refcnt = 1;
}