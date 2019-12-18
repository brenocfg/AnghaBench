#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_fault_buffer {TYPE_1__* fault; } ;
struct nvkm_event {int dummy; } ;
struct TYPE_2__ {struct nvkm_event event; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NVB069_V0_NTFY_FAULT ; 
 struct nvkm_fault_buffer* nvkm_fault_buffer (struct nvkm_object*) ; 

__attribute__((used)) static int
nvkm_ufault_ntfy(struct nvkm_object *object, u32 type,
		 struct nvkm_event **pevent)
{
	struct nvkm_fault_buffer *buffer = nvkm_fault_buffer(object);
	if (type == NVB069_V0_NTFY_FAULT) {
		*pevent = &buffer->fault->event;
		return 0;
	}
	return -EINVAL;
}