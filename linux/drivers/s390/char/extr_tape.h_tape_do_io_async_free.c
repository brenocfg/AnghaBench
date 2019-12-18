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
struct tape_request {int /*<<< orphan*/ * callback_data; void* callback; } ;
struct tape_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tape_do_io_async (struct tape_device*,struct tape_request*) ; 
 scalar_t__ tape_free_request ; 

__attribute__((used)) static inline void
tape_do_io_async_free(struct tape_device *device, struct tape_request *request)
{
	request->callback = (void *) tape_free_request;
	request->callback_data = NULL;
	tape_do_io_async(device, request);
}