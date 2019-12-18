#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* m_pool_p ;
typedef  int /*<<< orphan*/  m_pool_ident_t ;
struct TYPE_7__ {TYPE_1__* next; } ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  free_mem_cluster; int /*<<< orphan*/  get_mem_cluster; int /*<<< orphan*/  dev_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ___free_dma_mem_cluster ; 
 int /*<<< orphan*/  ___get_dma_mem_cluster ; 
 TYPE_1__* __sym_calloc (TYPE_2__*,int,char*) ; 
 TYPE_2__ mp0 ; 

__attribute__((used)) static m_pool_p ___cre_dma_pool(m_pool_ident_t dev_dmat)
{
	m_pool_p mp = __sym_calloc(&mp0, sizeof(*mp), "MPOOL");
	if (mp) {
		mp->dev_dmat = dev_dmat;
		mp->get_mem_cluster = ___get_dma_mem_cluster;
#ifdef	SYM_MEM_FREE_UNUSED
		mp->free_mem_cluster = ___free_dma_mem_cluster;
#endif
		mp->next = mp0.next;
		mp0.next = mp;
		return mp;
	}
	return NULL;
}