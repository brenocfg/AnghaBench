#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mv_cesa_engine {int /*<<< orphan*/  load; } ;
struct TYPE_4__ {struct mv_cesa_engine* engines; TYPE_1__* caps; } ;
struct TYPE_3__ {int nengines; } ;

/* Variables and functions */
 scalar_t__ U32_MAX ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_2__* cesa_dev ; 

__attribute__((used)) static inline struct mv_cesa_engine *mv_cesa_select_engine(int weight)
{
	int i;
	u32 min_load = U32_MAX;
	struct mv_cesa_engine *selected = NULL;

	for (i = 0; i < cesa_dev->caps->nengines; i++) {
		struct mv_cesa_engine *engine = cesa_dev->engines + i;
		u32 load = atomic_read(&engine->load);
		if (load < min_load) {
			min_load = load;
			selected = engine;
		}
	}

	atomic_add(weight, &selected->load);

	return selected;
}