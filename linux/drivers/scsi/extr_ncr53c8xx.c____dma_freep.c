#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ vaddr; scalar_t__ baddr; struct TYPE_5__* next; } ;
typedef  TYPE_1__ m_vtob_s ;
struct TYPE_6__ {int /*<<< orphan*/  nump; int /*<<< orphan*/  bush; TYPE_1__** vtob; } ;
typedef  TYPE_2__ m_pool_s ;
typedef  scalar_t__ m_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int MEMO_PAGE_ORDER ; 
 int PAGE_SIZE ; 
 int VTOB_HASH_CODE (scalar_t__) ; 
 int /*<<< orphan*/  __m_free (int /*<<< orphan*/ *,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp0 ; 

__attribute__((used)) static void ___dma_freep(m_pool_s *mp, m_addr_t m)
{
	m_vtob_s **vbpp, *vbp;
	int hc = VTOB_HASH_CODE(m);

	vbpp = &mp->vtob[hc];
	while (*vbpp && (*vbpp)->vaddr != m)
		vbpp = &(*vbpp)->next;
	if (*vbpp) {
		vbp = *vbpp;
		*vbpp = (*vbpp)->next;
		dma_free_coherent(mp->bush, PAGE_SIZE<<MEMO_PAGE_ORDER,
				  (void *)vbp->vaddr, (dma_addr_t)vbp->baddr);
		__m_free(&mp0, vbp, sizeof(*vbp), "VTOB");
		--mp->nump;
	}
}