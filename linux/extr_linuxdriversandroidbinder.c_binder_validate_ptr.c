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
struct TYPE_2__ {scalar_t__ type; } ;
struct binder_buffer_object {TYPE_1__ hdr; } ;
struct binder_buffer {scalar_t__ data; } ;
typedef  scalar_t__ binder_size_t ;

/* Variables and functions */
 scalar_t__ BINDER_TYPE_PTR ; 

__attribute__((used)) static struct binder_buffer_object *binder_validate_ptr(struct binder_buffer *b,
							binder_size_t index,
							binder_size_t *start,
							binder_size_t num_valid)
{
	struct binder_buffer_object *buffer_obj;
	binder_size_t *offp;

	if (index >= num_valid)
		return NULL;

	offp = start + index;
	buffer_obj = (struct binder_buffer_object *)(b->data + *offp);
	if (buffer_obj->hdr.type != BINDER_TYPE_PTR)
		return NULL;

	return buffer_obj;
}