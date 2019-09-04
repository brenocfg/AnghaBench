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
struct thin_c {int /*<<< orphan*/  thin_md; } ;
struct pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_internal_resume (int /*<<< orphan*/ ) ; 
 struct thin_c* get_first_thin (struct pool*) ; 
 struct thin_c* get_next_thin (struct pool*,struct thin_c*) ; 

__attribute__((used)) static void pool_resume_active_thins(struct pool *pool)
{
	struct thin_c *tc;

	/* Resume all active thin devices */
	tc = get_first_thin(pool);
	while (tc) {
		dm_internal_resume(tc->thin_md);
		tc = get_next_thin(pool, tc);
	}
}