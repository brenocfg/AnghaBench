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
struct kfd_process_device {int /*<<< orphan*/  alloc_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 

void kfd_process_device_remove_obj_handle(struct kfd_process_device *pdd,
					int handle)
{
	if (handle >= 0)
		idr_remove(&pdd->alloc_idr, handle);
}