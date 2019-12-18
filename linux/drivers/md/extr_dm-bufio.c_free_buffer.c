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
struct dm_bufio_client {int /*<<< orphan*/  slab_buffer; } ;
struct dm_buffer {int /*<<< orphan*/  data_mode; int /*<<< orphan*/  data; struct dm_bufio_client* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_buffer_data (struct dm_bufio_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dm_buffer*) ; 

__attribute__((used)) static void free_buffer(struct dm_buffer *b)
{
	struct dm_bufio_client *c = b->c;

	free_buffer_data(c, b->data, b->data_mode);
	kmem_cache_free(c->slab_buffer, b);
}