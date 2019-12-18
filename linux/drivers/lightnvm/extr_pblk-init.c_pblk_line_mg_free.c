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
struct pblk_line_mgmt {int /*<<< orphan*/  bitmap_cache; int /*<<< orphan*/  bitmap_pool; TYPE_1__** eline_meta; TYPE_1__** sline_meta; TYPE_1__* vsc_list; TYPE_1__* bb_aux; TYPE_1__* bb_template; } ;
struct pblk {struct pblk_line_mgmt l_mg; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int PBLK_DATA_LINES ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pblk_line_mg_free(struct pblk *pblk)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	int i;

	kfree(l_mg->bb_template);
	kfree(l_mg->bb_aux);
	kfree(l_mg->vsc_list);

	for (i = 0; i < PBLK_DATA_LINES; i++) {
		kfree(l_mg->sline_meta[i]);
		kvfree(l_mg->eline_meta[i]->buf);
		kfree(l_mg->eline_meta[i]);
	}

	mempool_destroy(l_mg->bitmap_pool);
	kmem_cache_destroy(l_mg->bitmap_cache);
}