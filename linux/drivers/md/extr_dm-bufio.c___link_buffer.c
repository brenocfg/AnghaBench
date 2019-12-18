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
struct dm_bufio_client {int /*<<< orphan*/ * lru; int /*<<< orphan*/ * n_buffers; } ;
struct dm_buffer {int list_mode; int /*<<< orphan*/  last_accessed; struct dm_bufio_client* c; int /*<<< orphan*/  lru_list; int /*<<< orphan*/  block; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  __insert (struct dm_bufio_client*,struct dm_buffer*) ; 
 int /*<<< orphan*/  adjust_total_allocated (struct dm_buffer*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __link_buffer(struct dm_buffer *b, sector_t block, int dirty)
{
	struct dm_bufio_client *c = b->c;

	c->n_buffers[dirty]++;
	b->block = block;
	b->list_mode = dirty;
	list_add(&b->lru_list, &c->lru[dirty]);
	__insert(b->c, b);
	b->last_accessed = jiffies;

	adjust_total_allocated(b, false);
}