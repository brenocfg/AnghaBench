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
typedef  int /*<<< orphan*/  VCHI_SERVICE_HANDLE_T ;

/* Variables and functions */
 int vchi_msg_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  vchi_queue_kernel_message_callback ; 

int
vchi_queue_kernel_message(VCHI_SERVICE_HANDLE_T handle,
			  void *data,
			  unsigned int size)
{
	return vchi_msg_queue(handle,
			      vchi_queue_kernel_message_callback,
			      data,
			      size);
}