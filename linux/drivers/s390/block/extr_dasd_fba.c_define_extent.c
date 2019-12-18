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
struct ccw1 {int count; scalar_t__ cda; scalar_t__ flags; int /*<<< orphan*/  cmd_code; } ;
struct TYPE_2__ {int perm; } ;
struct DE_fba_data {int blk_size; int ext_loc; int ext_end; TYPE_1__ mask; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FBA_CCW_DEFINE_EXTENT ; 
 int READ ; 
 int WRITE ; 
 scalar_t__ __pa (struct DE_fba_data*) ; 
 int /*<<< orphan*/  memset (struct DE_fba_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
define_extent(struct ccw1 * ccw, struct DE_fba_data *data, int rw,
	      int blksize, int beg, int nr)
{
	ccw->cmd_code = DASD_FBA_CCW_DEFINE_EXTENT;
	ccw->flags = 0;
	ccw->count = 16;
	ccw->cda = (__u32) __pa(data);
	memset(data, 0, sizeof (struct DE_fba_data));
	if (rw == WRITE)
		(data->mask).perm = 0x0;
	else if (rw == READ)
		(data->mask).perm = 0x1;
	else
		data->mask.perm = 0x2;
	data->blk_size = blksize;
	data->ext_loc = beg;
	data->ext_end = nr - 1;
}