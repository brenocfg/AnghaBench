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
struct tmc_drvdata {int dummy; } ;
struct perf_event {int cpu; } ;
struct etr_perf_buffer {struct etr_buf* etr_buf; struct tmc_drvdata* drvdata; } ;
struct etr_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct etr_perf_buffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct etr_buf*) ; 
 int NUMA_NO_NODE ; 
 int cpu_to_node (int) ; 
 struct etr_buf* get_perf_etr_buf (struct tmc_drvdata*,struct perf_event*,int,void**,int) ; 
 int /*<<< orphan*/  kfree (struct etr_perf_buffer*) ; 
 struct etr_perf_buffer* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct etr_perf_buffer *
tmc_etr_setup_perf_buf(struct tmc_drvdata *drvdata, struct perf_event *event,
		       int nr_pages, void **pages, bool snapshot)
{
	int node;
	struct etr_buf *etr_buf;
	struct etr_perf_buffer *etr_perf;

	node = (event->cpu == -1) ? NUMA_NO_NODE : cpu_to_node(event->cpu);

	etr_perf = kzalloc_node(sizeof(*etr_perf), GFP_KERNEL, node);
	if (!etr_perf)
		return ERR_PTR(-ENOMEM);

	etr_buf = get_perf_etr_buf(drvdata, event, nr_pages, pages, snapshot);
	if (!IS_ERR(etr_buf))
		goto done;

	kfree(etr_perf);
	return ERR_PTR(-ENOMEM);

done:
	/*
	 * Keep a reference to the ETR this buffer has been allocated for
	 * in order to have access to the IDR in tmc_free_etr_buffer().
	 */
	etr_perf->drvdata = drvdata;
	etr_perf->etr_buf = etr_buf;

	return etr_perf;
}