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
typedef  scalar_t__ u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_notify {int types; int /*<<< orphan*/  index; scalar_t__ size; } ;
struct nvkm_fault_buffer {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOSYS ; 
 struct nvkm_fault_buffer* nvkm_fault_buffer (struct nvkm_object*) ; 

__attribute__((used)) static int
nvkm_fault_ntfy_ctor(struct nvkm_object *object, void *argv, u32 argc,
		     struct nvkm_notify *notify)
{
	struct nvkm_fault_buffer *buffer = nvkm_fault_buffer(object);
	if (argc == 0) {
		notify->size  = 0;
		notify->types = 1;
		notify->index = buffer->id;
		return 0;
	}
	return -ENOSYS;
}