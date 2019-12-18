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
struct dm_bufio_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __flush_write_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __write_dirty_buffers_async (struct dm_bufio_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_bufio_in_request () ; 
 int /*<<< orphan*/  dm_bufio_lock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  dm_bufio_unlock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  write_list ; 

void dm_bufio_write_dirty_buffers_async(struct dm_bufio_client *c)
{
	LIST_HEAD(write_list);

	BUG_ON(dm_bufio_in_request());

	dm_bufio_lock(c);
	__write_dirty_buffers_async(c, 0, &write_list);
	dm_bufio_unlock(c);
	__flush_write_list(&write_list);
}