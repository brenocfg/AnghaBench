#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* m_vtob_p ;
typedef  TYPE_2__* m_pool_p ;
struct TYPE_8__ {int /*<<< orphan*/  nump; TYPE_1__** vtob; } ;
struct TYPE_7__ {void* vaddr; struct TYPE_7__* next; } ;

/* Variables and functions */
 int VTOB_HASH_CODE (void*) ; 
 int /*<<< orphan*/  __sym_mfree (int /*<<< orphan*/ *,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  mp0 ; 
 int /*<<< orphan*/  sym_m_free_dma_mem_cluster (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void ___free_dma_mem_cluster(m_pool_p mp, void *m)
{
	m_vtob_p *vbpp, vbp;
	int hc = VTOB_HASH_CODE(m);

	vbpp = &mp->vtob[hc];
	while (*vbpp && (*vbpp)->vaddr != m)
		vbpp = &(*vbpp)->next;
	if (*vbpp) {
		vbp = *vbpp;
		*vbpp = (*vbpp)->next;
		sym_m_free_dma_mem_cluster(mp, vbp);
		__sym_mfree(&mp0, vbp, sizeof(*vbp), "VTOB");
		--mp->nump;
	}
}