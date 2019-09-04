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
struct swap_eb {struct rb_root* root; } ;
struct rb_root {int dummy; } ;
struct mtdswap_dev {TYPE_1__* trees; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; struct rb_root root; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mtdswap_rb_add (struct rb_root*,struct swap_eb*) ; 
 int /*<<< orphan*/  mtdswap_eb_detach (struct mtdswap_dev*,struct swap_eb*) ; 

__attribute__((used)) static void mtdswap_rb_add(struct mtdswap_dev *d, struct swap_eb *eb, int idx)
{
	struct rb_root *root;

	if (eb->root == &d->trees[idx].root)
		return;

	mtdswap_eb_detach(d, eb);
	root = &d->trees[idx].root;
	__mtdswap_rb_add(root, eb);
	eb->root = root;
	d->trees[idx].count++;
}