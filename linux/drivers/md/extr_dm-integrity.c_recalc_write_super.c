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
struct dm_integrity_c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 scalar_t__ dm_integrity_failed (struct dm_integrity_c*) ; 
 int /*<<< orphan*/  dm_integrity_flush_buffers (struct dm_integrity_c*) ; 
 int /*<<< orphan*/  dm_integrity_io_error (struct dm_integrity_c*,char*,int) ; 
 int sync_rw_sb (struct dm_integrity_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void recalc_write_super(struct dm_integrity_c *ic)
{
	int r;

	dm_integrity_flush_buffers(ic);
	if (dm_integrity_failed(ic))
		return;

	r = sync_rw_sb(ic, REQ_OP_WRITE, 0);
	if (unlikely(r))
		dm_integrity_io_error(ic, "writing superblock", r);
}