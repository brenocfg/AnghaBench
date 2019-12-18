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
struct list_head {int dummy; } ;
struct dm_bufio_client {int* n_buffers; } ;

/* Variables and functions */
 int DM_BUFIO_WRITEBACK_RATIO ; 
 size_t LIST_CLEAN ; 
 size_t LIST_DIRTY ; 
 int /*<<< orphan*/  __write_dirty_buffers_async (struct dm_bufio_client*,int,struct list_head*) ; 

__attribute__((used)) static void __check_watermark(struct dm_bufio_client *c,
			      struct list_head *write_list)
{
	if (c->n_buffers[LIST_DIRTY] > c->n_buffers[LIST_CLEAN] * DM_BUFIO_WRITEBACK_RATIO)
		__write_dirty_buffers_async(c, 1, write_list);
}