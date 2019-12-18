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
typedef  int /*<<< orphan*/  u64 ;
struct seq_file {int dummy; } ;
struct ce_array {int n; int flags; int decays_done; int /*<<< orphan*/  pfns_poisoned; int /*<<< orphan*/  ces_entered; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT (int /*<<< orphan*/ ) ; 
 size_t DECAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFN (int /*<<< orphan*/ ) ; 
 int action_threshold ; 
 int /*<<< orphan*/ * bins ; 
 struct ce_array ce_arr ; 
 int /*<<< orphan*/  ce_mutex ; 
 int decay_interval ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int array_dump(struct seq_file *m, void *v)
{
	struct ce_array *ca = &ce_arr;
	int i;

	mutex_lock(&ce_mutex);

	seq_printf(m, "{ n: %d\n", ca->n);
	for (i = 0; i < ca->n; i++) {
		u64 this = PFN(ca->array[i]);

		seq_printf(m, " %3d: [%016llx|%s|%03llx]\n",
			   i, this, bins[DECAY(ca->array[i])], COUNT(ca->array[i]));
	}

	seq_printf(m, "}\n");

	seq_printf(m, "Stats:\nCEs: %llu\nofflined pages: %llu\n",
		   ca->ces_entered, ca->pfns_poisoned);

	seq_printf(m, "Flags: 0x%x\n", ca->flags);

	seq_printf(m, "Decay interval: %lld seconds\n", decay_interval);
	seq_printf(m, "Decays: %lld\n", ca->decays_done);

	seq_printf(m, "Action threshold: %lld\n", action_threshold);

	mutex_unlock(&ce_mutex);

	return 0;
}