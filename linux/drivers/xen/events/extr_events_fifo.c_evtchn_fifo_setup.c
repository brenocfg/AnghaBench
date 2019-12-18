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
struct irq_info {unsigned int evtchn; } ;
struct evtchn_expand_array {int /*<<< orphan*/  array_gfn; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int EVENT_WORDS_PER_PAGE ; 
 int /*<<< orphan*/  EVTCHNOP_expand_array ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_expand_array*) ; 
 unsigned int MAX_EVENT_ARRAY_PAGES ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 void** event_array ; 
 unsigned int event_array_pages ; 
 int /*<<< orphan*/  free_unused_array_pages () ; 
 int /*<<< orphan*/  init_array_page (void*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  virt_to_gfn (void*) ; 

__attribute__((used)) static int evtchn_fifo_setup(struct irq_info *info)
{
	unsigned port = info->evtchn;
	unsigned new_array_pages;
	int ret;

	new_array_pages = port / EVENT_WORDS_PER_PAGE + 1;

	if (new_array_pages > MAX_EVENT_ARRAY_PAGES)
		return -EINVAL;

	while (event_array_pages < new_array_pages) {
		void *array_page;
		struct evtchn_expand_array expand_array;

		/* Might already have a page if we've resumed. */
		array_page = event_array[event_array_pages];
		if (!array_page) {
			array_page = (void *)__get_free_page(GFP_KERNEL);
			if (array_page == NULL) {
				ret = -ENOMEM;
				goto error;
			}
			event_array[event_array_pages] = array_page;
		}

		/* Mask all events in this page before adding it. */
		init_array_page(array_page);

		expand_array.array_gfn = virt_to_gfn(array_page);

		ret = HYPERVISOR_event_channel_op(EVTCHNOP_expand_array, &expand_array);
		if (ret < 0)
			goto error;

		event_array_pages++;
	}
	return 0;

  error:
	if (event_array_pages == 0)
		panic("xen: unable to expand event array with initial page (%d)\n", ret);
	else
		pr_err("unable to expand event array (%d)\n", ret);
	free_unused_array_pages();
	return ret;
}