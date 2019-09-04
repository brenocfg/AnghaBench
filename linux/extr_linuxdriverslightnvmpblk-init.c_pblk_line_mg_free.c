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
struct pblk_line_mgmt {TYPE_1__** eline_meta; int /*<<< orphan*/  emeta_alloc_type; TYPE_1__** sline_meta; TYPE_1__* vsc_list; TYPE_1__* bb_aux; TYPE_1__* bb_template; } ;
struct pblk {struct pblk_line_mgmt l_mg; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int PBLK_DATA_LINES ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pblk_mfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pblk_line_mg_free(struct pblk *pblk)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	int i;

	kfree(l_mg->bb_template);
	kfree(l_mg->bb_aux);
	kfree(l_mg->vsc_list);

	for (i = 0; i < PBLK_DATA_LINES; i++) {
		kfree(l_mg->sline_meta[i]);
		pblk_mfree(l_mg->eline_meta[i]->buf, l_mg->emeta_alloc_type);
		kfree(l_mg->eline_meta[i]);
	}
}