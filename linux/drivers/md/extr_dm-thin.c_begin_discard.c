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
struct thin_c {int dummy; } ;
struct discard_op {int /*<<< orphan*/ * bio; struct bio* parent_bio; int /*<<< orphan*/  plug; struct thin_c* tc; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  blk_start_plug (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void begin_discard(struct discard_op *op, struct thin_c *tc, struct bio *parent)
{
	BUG_ON(!parent);

	op->tc = tc;
	blk_start_plug(&op->plug);
	op->parent_bio = parent;
	op->bio = NULL;
}