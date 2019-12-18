#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct m_pool {struct m_pool* next; } ;
typedef  struct m_pool m_pool_s ;
struct TYPE_3__ {struct m_pool* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  __m_free (TYPE_1__*,struct m_pool*,int,char*) ; 
 TYPE_1__ mp0 ; 

__attribute__((used)) static void ___del_dma_pool(m_pool_s *p)
{
	struct m_pool **pp = &mp0.next;

	while (*pp && *pp != p)
		pp = &(*pp)->next;
	if (*pp) {
		*pp = (*pp)->next;
		__m_free(&mp0, p, sizeof(*p), "MPOOL");
	}
}