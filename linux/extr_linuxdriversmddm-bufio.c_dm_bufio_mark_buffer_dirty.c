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
struct dm_buffer {TYPE_1__* c; } ;
struct TYPE_2__ {int /*<<< orphan*/  block_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_bufio_mark_partial_buffer_dirty (struct dm_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dm_bufio_mark_buffer_dirty(struct dm_buffer *b)
{
	dm_bufio_mark_partial_buffer_dirty(b, 0, b->c->block_size);
}