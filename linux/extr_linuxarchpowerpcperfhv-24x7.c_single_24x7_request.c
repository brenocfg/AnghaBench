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
struct perf_event {int dummy; } ;
struct hv_24x7_request_buffer {int dummy; } ;
struct hv_24x7_data_result_buffer {int /*<<< orphan*/  results; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int add_event_to_24x7_request (struct perf_event*,struct hv_24x7_request_buffer*) ; 
 int get_count_from_result (struct perf_event*,struct hv_24x7_data_result_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_24x7_reqb ; 
 int /*<<< orphan*/  hv_24x7_resb ; 
 int /*<<< orphan*/  init_24x7_request (struct hv_24x7_request_buffer*,struct hv_24x7_data_result_buffer*) ; 
 int make_24x7_request (struct hv_24x7_request_buffer*,struct hv_24x7_data_result_buffer*) ; 
 int /*<<< orphan*/  put_cpu_var (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int single_24x7_request(struct perf_event *event, u64 *count)
{
	int ret;
	struct hv_24x7_request_buffer *request_buffer;
	struct hv_24x7_data_result_buffer *result_buffer;

	BUILD_BUG_ON(sizeof(*request_buffer) > 4096);
	BUILD_BUG_ON(sizeof(*result_buffer) > 4096);

	request_buffer = (void *)get_cpu_var(hv_24x7_reqb);
	result_buffer = (void *)get_cpu_var(hv_24x7_resb);

	init_24x7_request(request_buffer, result_buffer);

	ret = add_event_to_24x7_request(event, request_buffer);
	if (ret)
		goto out;

	ret = make_24x7_request(request_buffer, result_buffer);
	if (ret)
		goto out;

	/* process result from hcall */
	ret = get_count_from_result(event, result_buffer,
				    result_buffer->results, count, NULL);

out:
	put_cpu_var(hv_24x7_reqb);
	put_cpu_var(hv_24x7_resb);
	return ret;
}