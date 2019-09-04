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
struct cache_set {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  failed; int /*<<< orphan*/  floats; int /*<<< orphan*/  bytes_unwritten; int /*<<< orphan*/  bytes_written; int /*<<< orphan*/  sets_unwritten; int /*<<< orphan*/  sets_written; } ;
struct bset_stats_op {TYPE_1__ stats; int /*<<< orphan*/  nodes; int /*<<< orphan*/  op; } ;
typedef  int /*<<< orphan*/  op ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ZERO_KEY ; 
 int /*<<< orphan*/  bch_btree_bset_stats ; 
 int bch_btree_map_nodes (int /*<<< orphan*/ *,struct cache_set*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_btree_op_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct bset_stats_op*,int /*<<< orphan*/ ,int) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bch_bset_print_stats(struct cache_set *c, char *buf)
{
	struct bset_stats_op op;
	int ret;

	memset(&op, 0, sizeof(op));
	bch_btree_op_init(&op.op, -1);

	ret = bch_btree_map_nodes(&op.op, c, &ZERO_KEY, bch_btree_bset_stats);
	if (ret < 0)
		return ret;

	return snprintf(buf, PAGE_SIZE,
			"btree nodes:		%zu\n"
			"written sets:		%zu\n"
			"unwritten sets:		%zu\n"
			"written key bytes:	%zu\n"
			"unwritten key bytes:	%zu\n"
			"floats:			%zu\n"
			"failed:			%zu\n",
			op.nodes,
			op.stats.sets_written, op.stats.sets_unwritten,
			op.stats.bytes_written, op.stats.bytes_unwritten,
			op.stats.floats, op.stats.failed);
}