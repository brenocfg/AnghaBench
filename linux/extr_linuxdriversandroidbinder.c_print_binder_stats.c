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
struct seq_file {int dummy; } ;
struct binder_stats {int /*<<< orphan*/ * obj_deleted; int /*<<< orphan*/ * obj_created; int /*<<< orphan*/ * br; int /*<<< orphan*/ * bc; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * binder_command_strings ; 
 int /*<<< orphan*/ * binder_objstat_strings ; 
 int /*<<< orphan*/ * binder_return_strings ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static void print_binder_stats(struct seq_file *m, const char *prefix,
			       struct binder_stats *stats)
{
	int i;

	BUILD_BUG_ON(ARRAY_SIZE(stats->bc) !=
		     ARRAY_SIZE(binder_command_strings));
	for (i = 0; i < ARRAY_SIZE(stats->bc); i++) {
		int temp = atomic_read(&stats->bc[i]);

		if (temp)
			seq_printf(m, "%s%s: %d\n", prefix,
				   binder_command_strings[i], temp);
	}

	BUILD_BUG_ON(ARRAY_SIZE(stats->br) !=
		     ARRAY_SIZE(binder_return_strings));
	for (i = 0; i < ARRAY_SIZE(stats->br); i++) {
		int temp = atomic_read(&stats->br[i]);

		if (temp)
			seq_printf(m, "%s%s: %d\n", prefix,
				   binder_return_strings[i], temp);
	}

	BUILD_BUG_ON(ARRAY_SIZE(stats->obj_created) !=
		     ARRAY_SIZE(binder_objstat_strings));
	BUILD_BUG_ON(ARRAY_SIZE(stats->obj_created) !=
		     ARRAY_SIZE(stats->obj_deleted));
	for (i = 0; i < ARRAY_SIZE(stats->obj_created); i++) {
		int created = atomic_read(&stats->obj_created[i]);
		int deleted = atomic_read(&stats->obj_deleted[i]);

		if (created || deleted)
			seq_printf(m, "%s%s: active %d total %d\n",
				prefix,
				binder_objstat_strings[i],
				created - deleted,
				created);
	}
}