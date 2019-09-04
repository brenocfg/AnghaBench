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
struct hv_24x7_request_buffer {int /*<<< orphan*/  interface_version; } ;
struct hv_24x7_data_result_buffer {int /*<<< orphan*/  interface_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  H24x7_DATA_BUFFER_SIZE ; 
 int /*<<< orphan*/  interface_version ; 
 int /*<<< orphan*/  memset (struct hv_24x7_request_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_24x7_request(struct hv_24x7_request_buffer *request_buffer,
			      struct hv_24x7_data_result_buffer *result_buffer)
{

	memset(request_buffer, 0, H24x7_DATA_BUFFER_SIZE);
	memset(result_buffer, 0, H24x7_DATA_BUFFER_SIZE);

	request_buffer->interface_version = interface_version;
	/* memset above set request_buffer->num_requests to 0 */
}