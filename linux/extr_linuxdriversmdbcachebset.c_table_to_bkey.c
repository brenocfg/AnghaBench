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
struct bset_tree {int /*<<< orphan*/ * prev; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 struct bkey* cacheline_to_bkey (struct bset_tree*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bkey *table_to_bkey(struct bset_tree *t, unsigned int cacheline)
{
	return cacheline_to_bkey(t, cacheline, t->prev[cacheline]);
}