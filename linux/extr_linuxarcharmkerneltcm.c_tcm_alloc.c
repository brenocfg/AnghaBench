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

/* Variables and functions */
 unsigned long gen_pool_alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tcm_pool ; 

void *tcm_alloc(size_t len)
{
	unsigned long vaddr;

	if (!tcm_pool)
		return NULL;

	vaddr = gen_pool_alloc(tcm_pool, len);
	if (!vaddr)
		return NULL;

	return (void *) vaddr;
}