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
struct vchiq_io_copy_callback_context {unsigned long elements_to_go; scalar_t__ element_offset; struct vchiq_element* element; } ;
struct vchiq_element {scalar_t__ size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  vchiq_ioc_copy_element_data ; 
 int /*<<< orphan*/  vchiq_queue_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vchiq_io_copy_callback_context*,size_t) ; 

__attribute__((used)) static VCHIQ_STATUS_T
vchiq_ioc_queue_message(VCHIQ_SERVICE_HANDLE_T handle,
			struct vchiq_element *elements,
			unsigned long count)
{
	struct vchiq_io_copy_callback_context context;
	unsigned long i;
	size_t total_size = 0;

	context.element = elements;
	context.element_offset = 0;
	context.elements_to_go = count;

	for (i = 0; i < count; i++) {
		if (!elements[i].data && elements[i].size != 0)
			return -EFAULT;

		total_size += elements[i].size;
	}

	return vchiq_queue_message(handle, vchiq_ioc_copy_element_data,
				   &context, total_size);
}