#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvkm_object {int dummy; } ;
struct nvkm_fault_buffer {TYPE_3__* fault; } ;
struct TYPE_6__ {TYPE_2__* func; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fini ) (struct nvkm_fault_buffer*) ;} ;
struct TYPE_5__ {TYPE_1__ buffer; } ;

/* Variables and functions */
 struct nvkm_fault_buffer* nvkm_fault_buffer (struct nvkm_object*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_fault_buffer*) ; 

__attribute__((used)) static int
nvkm_ufault_fini(struct nvkm_object *object, bool suspend)
{
	struct nvkm_fault_buffer *buffer = nvkm_fault_buffer(object);
	buffer->fault->func->buffer.fini(buffer);
	return 0;
}