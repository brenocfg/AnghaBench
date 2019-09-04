#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct output {int dummy; } ;
struct host1x {TYPE_1__* syncpt; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  host1x_debug_output (struct output*,char*,...) ; 
 scalar_t__ host1x_syncpt_load (TYPE_1__*) ; 
 scalar_t__ host1x_syncpt_load_wait_base (TYPE_1__*) ; 
 unsigned int host1x_syncpt_nb_bases (struct host1x*) ; 
 unsigned int host1x_syncpt_nb_pts (struct host1x*) ; 
 scalar_t__ host1x_syncpt_read_max (TYPE_1__*) ; 

__attribute__((used)) static void show_syncpts(struct host1x *m, struct output *o)
{
	unsigned int i;

	host1x_debug_output(o, "---- syncpts ----\n");

	for (i = 0; i < host1x_syncpt_nb_pts(m); i++) {
		u32 max = host1x_syncpt_read_max(m->syncpt + i);
		u32 min = host1x_syncpt_load(m->syncpt + i);

		if (!min && !max)
			continue;

		host1x_debug_output(o, "id %u (%s) min %d max %d\n",
				    i, m->syncpt[i].name, min, max);
	}

	for (i = 0; i < host1x_syncpt_nb_bases(m); i++) {
		u32 base_val;

		base_val = host1x_syncpt_load_wait_base(m->syncpt + i);
		if (base_val)
			host1x_debug_output(o, "waitbase id %u val %d\n", i,
					    base_val);
	}

	host1x_debug_output(o, "\n");
}