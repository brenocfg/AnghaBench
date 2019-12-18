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
struct resource_pool {int pipe_count; struct hubp** hubps; } ;
struct hubp {int inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

__attribute__((used)) static struct hubp *get_hubp_by_inst(struct resource_pool *res_pool, int mpcc_inst)
{
	int i;

	for (i = 0; i < res_pool->pipe_count; i++) {
		if (res_pool->hubps[i]->inst == mpcc_inst)
			return res_pool->hubps[i];
	}
	ASSERT(false);
	return NULL;
}