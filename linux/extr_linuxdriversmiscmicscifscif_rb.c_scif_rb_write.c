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
typedef  int u32 ;
struct scif_rb {int current_write_offset; int size; void* rb_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  memcpy_torb (struct scif_rb*,void*,void*,int) ; 
 int scif_rb_space (struct scif_rb*) ; 

int scif_rb_write(struct scif_rb *rb, void *msg, u32 size)
{
	void *header;

	if (scif_rb_space(rb) < size)
		return -ENOMEM;
	header = rb->rb_base + rb->current_write_offset;
	memcpy_torb(rb, header, msg, size);
	/*
	 * Wait until scif_rb_commit(). Update the local ring
	 * buffer data, not the shared data until commit.
	 */
	rb->current_write_offset =
		(rb->current_write_offset + size) & (rb->size - 1);
	return 0;
}