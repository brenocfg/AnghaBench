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
struct nouveau_svm_fault_buffer {int entries; int /*<<< orphan*/  object; int /*<<< orphan*/  notify; scalar_t__* fault; } ;
struct nouveau_svm {struct nouveau_svm_fault_buffer* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  kvfree (scalar_t__*) ; 
 int /*<<< orphan*/  nouveau_svm_fault_buffer_fini (struct nouveau_svm*,int) ; 
 int /*<<< orphan*/  nvif_notify_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_object_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_svm_fault_buffer_dtor(struct nouveau_svm *svm, int id)
{
	struct nouveau_svm_fault_buffer *buffer = &svm->buffer[id];
	int i;

	if (buffer->fault) {
		for (i = 0; buffer->fault[i] && i < buffer->entries; i++)
			kfree(buffer->fault[i]);
		kvfree(buffer->fault);
	}

	nouveau_svm_fault_buffer_fini(svm, id);

	nvif_notify_fini(&buffer->notify);
	nvif_object_fini(&buffer->object);
}