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
struct thin_c {int /*<<< orphan*/  pool; } ;
struct noflush_work {int /*<<< orphan*/  pw; struct thin_c* tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  pool_work_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (struct work_struct*)) ; 

__attribute__((used)) static void noflush_work(struct thin_c *tc, void (*fn)(struct work_struct *))
{
	struct noflush_work w;

	w.tc = tc;
	pool_work_wait(&w.pw, tc->pool, fn);
}