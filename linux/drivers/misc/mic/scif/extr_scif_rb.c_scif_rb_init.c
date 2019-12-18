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
typedef  int u8 ;
typedef  void* u32 ;
struct scif_rb {int size; void** read_ptr; void** write_ptr; void* current_write_offset; void* current_read_offset; void* rb_base; } ;

/* Variables and functions */

void scif_rb_init(struct scif_rb *rb, u32 *read_ptr, u32 *write_ptr,
		  void *rb_base, u8 size)
{
	rb->rb_base = rb_base;
	rb->size = (1 << size);
	rb->read_ptr = read_ptr;
	rb->write_ptr = write_ptr;
	rb->current_read_offset = *read_ptr;
	rb->current_write_offset = *write_ptr;
}