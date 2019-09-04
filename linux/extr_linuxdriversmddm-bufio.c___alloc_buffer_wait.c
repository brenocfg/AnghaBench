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
struct dm_bufio_client {int /*<<< orphan*/  (* alloc_callback ) (struct dm_buffer*) ;} ;
struct dm_buffer {int dummy; } ;
typedef  enum new_flag { ____Placeholder_new_flag } new_flag ;

/* Variables and functions */
 struct dm_buffer* __alloc_buffer_wait_no_callback (struct dm_bufio_client*,int) ; 
 int /*<<< orphan*/  stub1 (struct dm_buffer*) ; 

__attribute__((used)) static struct dm_buffer *__alloc_buffer_wait(struct dm_bufio_client *c, enum new_flag nf)
{
	struct dm_buffer *b = __alloc_buffer_wait_no_callback(c, nf);

	if (!b)
		return NULL;

	if (c->alloc_callback)
		c->alloc_callback(b);

	return b;
}