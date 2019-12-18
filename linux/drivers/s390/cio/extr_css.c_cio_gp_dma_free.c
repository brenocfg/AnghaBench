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
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_free (struct gen_pool*,unsigned long,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void cio_gp_dma_free(struct gen_pool *gp_dma, void *cpu_addr, size_t size)
{
	if (!cpu_addr)
		return;
	memset(cpu_addr, 0, size);
	gen_pool_free(gp_dma, (unsigned long) cpu_addr, size);
}