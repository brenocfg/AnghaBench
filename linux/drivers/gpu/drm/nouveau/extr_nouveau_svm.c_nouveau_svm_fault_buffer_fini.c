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
struct nouveau_svm_fault_buffer {int /*<<< orphan*/  notify; } ;
struct nouveau_svm {struct nouveau_svm_fault_buffer* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvif_notify_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_svm_fault_buffer_fini(struct nouveau_svm *svm, int id)
{
	struct nouveau_svm_fault_buffer *buffer = &svm->buffer[id];
	nvif_notify_put(&buffer->notify);
}