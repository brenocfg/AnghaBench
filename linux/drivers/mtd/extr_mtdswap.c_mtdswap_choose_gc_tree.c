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
struct mtdswap_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAN ; 
 int /*<<< orphan*/  DIRTY ; 
 int /*<<< orphan*/  FAILING ; 
 int MTDSWAP_CLEAN ; 
 int MTDSWAP_FAILING ; 
 scalar_t__ TREE_EMPTY (struct mtdswap_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_NONEMPTY (struct mtdswap_dev*,int /*<<< orphan*/ ) ; 
 int __mtdswap_choose_gc_tree (struct mtdswap_dev*) ; 
 int mtdswap_choose_wl_tree (struct mtdswap_dev*) ; 

__attribute__((used)) static int mtdswap_choose_gc_tree(struct mtdswap_dev *d,
				unsigned int background)
{
	int idx;

	if (TREE_NONEMPTY(d, FAILING) &&
		(background || (TREE_EMPTY(d, CLEAN) && TREE_EMPTY(d, DIRTY))))
		return MTDSWAP_FAILING;

	idx = mtdswap_choose_wl_tree(d);
	if (idx >= MTDSWAP_CLEAN)
		return idx;

	return __mtdswap_choose_gc_tree(d);
}