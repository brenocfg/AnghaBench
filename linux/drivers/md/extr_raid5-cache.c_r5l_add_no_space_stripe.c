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
struct stripe_head {int /*<<< orphan*/  log_list; } ;
struct r5l_log {int /*<<< orphan*/  no_space_stripes_lock; int /*<<< orphan*/  no_space_stripes; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void r5l_add_no_space_stripe(struct r5l_log *log,
					   struct stripe_head *sh)
{
	spin_lock(&log->no_space_stripes_lock);
	list_add_tail(&sh->log_list, &log->no_space_stripes);
	spin_unlock(&log->no_space_stripes_lock);
}