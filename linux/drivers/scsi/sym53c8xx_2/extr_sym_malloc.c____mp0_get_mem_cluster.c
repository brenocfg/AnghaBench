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
typedef  TYPE_1__* m_pool_p ;
struct TYPE_3__ {int /*<<< orphan*/  nump; } ;

/* Variables and functions */
 void* sym_get_mem_cluster () ; 

__attribute__((used)) static void *___mp0_get_mem_cluster(m_pool_p mp)
{
	void *m = sym_get_mem_cluster();
	if (m)
		++mp->nump;
	return m;
}