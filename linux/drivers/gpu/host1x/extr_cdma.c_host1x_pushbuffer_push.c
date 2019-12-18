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
typedef  void* u32 ;
struct push_buffer {int pos; scalar_t__ fence; scalar_t__ size; scalar_t__ mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void host1x_pushbuffer_push(struct push_buffer *pb, u32 op1, u32 op2)
{
	u32 *p = (u32 *)((void *)pb->mapped + pb->pos);

	WARN_ON(pb->pos == pb->fence);
	*(p++) = op1;
	*(p++) = op2;
	pb->pos += 8;

	if (pb->pos >= pb->size)
		pb->pos -= pb->size;
}