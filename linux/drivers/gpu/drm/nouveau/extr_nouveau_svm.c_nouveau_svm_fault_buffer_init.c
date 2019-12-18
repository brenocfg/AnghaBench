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
struct nvif_object {int dummy; } ;
struct nouveau_svm_fault_buffer {int /*<<< orphan*/  notify; void* put; void* get; int /*<<< orphan*/  putaddr; int /*<<< orphan*/  getaddr; } ;
struct nouveau_svm {TYPE_3__* drm; struct nouveau_svm_fault_buffer* buffer; } ;
struct TYPE_4__ {struct nvif_object object; } ;
struct TYPE_5__ {TYPE_1__ device; } ;
struct TYPE_6__ {TYPE_2__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVM_DBG (struct nouveau_svm*,char*,void*,void*) ; 
 int nvif_notify_get (int /*<<< orphan*/ *) ; 
 void* nvif_rd32 (struct nvif_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nouveau_svm_fault_buffer_init(struct nouveau_svm *svm, int id)
{
	struct nouveau_svm_fault_buffer *buffer = &svm->buffer[id];
	struct nvif_object *device = &svm->drm->client.device.object;
	buffer->get = nvif_rd32(device, buffer->getaddr);
	buffer->put = nvif_rd32(device, buffer->putaddr);
	SVM_DBG(svm, "get %08x put %08x (init)", buffer->get, buffer->put);
	return nvif_notify_get(&buffer->notify);
}