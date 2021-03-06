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
struct dm_integrity_c {int /*<<< orphan*/  bufio; } ;

/* Variables and functions */
 int dm_bufio_write_dirty_buffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_integrity_io_error (struct dm_integrity_c*,char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void dm_integrity_flush_buffers(struct dm_integrity_c *ic)
{
	int r;
	r = dm_bufio_write_dirty_buffers(ic->bufio);
	if (unlikely(r))
		dm_integrity_io_error(ic, "writing tags", r);
}