#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtdswap_dev {TYPE_2__* trees; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rb_node; } ;
struct TYPE_4__ {TYPE_1__ root; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAN ; 
 scalar_t__ LOW_FRAG_GC_THRESHOLD ; 
 int MTDSWAP_BITFLIP ; 
 int MTDSWAP_HIFRAG ; 
 int MTDSWAP_LOWFRAG ; 
 scalar_t__ TREE_COUNT (struct mtdswap_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __mtdswap_choose_gc_tree(struct mtdswap_dev *d)
{
	int idx, stopat;

	if (TREE_COUNT(d, CLEAN) < LOW_FRAG_GC_THRESHOLD)
		stopat = MTDSWAP_LOWFRAG;
	else
		stopat = MTDSWAP_HIFRAG;

	for (idx = MTDSWAP_BITFLIP; idx >= stopat; idx--)
		if (d->trees[idx].root.rb_node != NULL)
			return idx;

	return -1;
}