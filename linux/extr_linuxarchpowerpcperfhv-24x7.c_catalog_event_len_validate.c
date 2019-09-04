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
struct hv_24x7_event_data {int /*<<< orphan*/  length; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* event_end (struct hv_24x7_event_data*,void*) ; 
 int /*<<< orphan*/  event_fixed_portion_is_within (struct hv_24x7_event_data*,void*) ; 
 int /*<<< orphan*/  pr_devel (char*,size_t) ; 
 int /*<<< orphan*/  pr_info (char*,size_t,int,struct hv_24x7_event_data*) ; 
 int /*<<< orphan*/  pr_warn (char*,size_t,...) ; 

__attribute__((used)) static ssize_t catalog_event_len_validate(struct hv_24x7_event_data *event,
					  size_t event_idx,
					  size_t event_data_bytes,
					  size_t event_entry_count,
					  size_t offset, void *end)
{
	ssize_t ev_len;
	void *ev_end, *calc_ev_end;

	if (offset >= event_data_bytes)
		return -1;

	if (event_idx >= event_entry_count) {
		pr_devel("catalog event data has %zu bytes of padding after last event\n",
				event_data_bytes - offset);
		return -1;
	}

	if (!event_fixed_portion_is_within(event, end)) {
		pr_warn("event %zu fixed portion is not within range\n",
				event_idx);
		return -1;
	}

	ev_len = be16_to_cpu(event->length);

	if (ev_len % 16)
		pr_info("event %zu has length %zu not divisible by 16: event=%pK\n",
				event_idx, ev_len, event);

	ev_end = (__u8 *)event + ev_len;
	if (ev_end > end) {
		pr_warn("event %zu has .length=%zu, ends after buffer end: ev_end=%pK > end=%pK, offset=%zu\n",
				event_idx, ev_len, ev_end, end,
				offset);
		return -1;
	}

	calc_ev_end = event_end(event, end);
	if (!calc_ev_end) {
		pr_warn("event %zu has a calculated length which exceeds buffer length %zu: event=%pK end=%pK, offset=%zu\n",
			event_idx, event_data_bytes, event, end,
			offset);
		return -1;
	}

	if (calc_ev_end > ev_end) {
		pr_warn("event %zu exceeds it's own length: event=%pK, end=%pK, offset=%zu, calc_ev_end=%pK\n",
			event_idx, event, ev_end, offset, calc_ev_end);
		return -1;
	}

	return ev_len;
}