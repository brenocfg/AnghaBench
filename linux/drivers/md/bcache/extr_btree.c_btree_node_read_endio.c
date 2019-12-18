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
struct closure {int dummy; } ;
struct bio {struct closure* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  closure_put (struct closure*) ; 

__attribute__((used)) static void btree_node_read_endio(struct bio *bio)
{
	struct closure *cl = bio->bi_private;

	closure_put(cl);
}