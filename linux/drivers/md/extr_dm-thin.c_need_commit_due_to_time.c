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
struct pool {scalar_t__ last_commit_jiffies; } ;

/* Variables and functions */
 scalar_t__ COMMIT_PERIOD ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  time_in_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int need_commit_due_to_time(struct pool *pool)
{
	return !time_in_range(jiffies, pool->last_commit_jiffies,
			      pool->last_commit_jiffies + COMMIT_PERIOD);
}