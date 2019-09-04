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
struct TYPE_2__ {int bi_op; scalar_t__ bi_op_flags; } ;
struct log_c {int /*<<< orphan*/  header_location; TYPE_1__ io_req; } ;

/* Variables and functions */
 int dm_io (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rw_header(struct log_c *lc, int op)
{
	lc->io_req.bi_op = op;
	lc->io_req.bi_op_flags = 0;

	return dm_io(&lc->io_req, 1, &lc->header_location, NULL);
}