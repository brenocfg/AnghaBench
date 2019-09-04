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
struct seq_file {int dummy; } ;
struct sdma_rht_node {TYPE_2__** map; } ;
struct hfi1_devdata {int /*<<< orphan*/  sdma_rht; } ;
struct TYPE_4__ {int ctr; TYPE_1__** sde; } ;
struct TYPE_3__ {int this_idx; } ;

/* Variables and functions */
 int HFI1_MAX_VLS_SUPPORTED ; 
 struct sdma_rht_node* rhashtable_lookup_fast (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_rht_params ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

void sdma_seqfile_dump_cpu_list(struct seq_file *s,
				struct hfi1_devdata *dd,
				unsigned long cpuid)
{
	struct sdma_rht_node *rht_node;
	int i, j;

	rht_node = rhashtable_lookup_fast(dd->sdma_rht, &cpuid,
					  sdma_rht_params);
	if (!rht_node)
		return;

	seq_printf(s, "cpu%3lu: ", cpuid);
	for (i = 0; i < HFI1_MAX_VLS_SUPPORTED; i++) {
		if (!rht_node->map[i] || !rht_node->map[i]->ctr)
			continue;

		seq_printf(s, " vl%d: [", i);

		for (j = 0; j < rht_node->map[i]->ctr; j++) {
			if (!rht_node->map[i]->sde[j])
				continue;

			if (j > 0)
				seq_puts(s, ",");

			seq_printf(s, " sdma%2d",
				   rht_node->map[i]->sde[j]->this_idx);
		}
		seq_puts(s, " ]");
	}

	seq_puts(s, "\n");
}