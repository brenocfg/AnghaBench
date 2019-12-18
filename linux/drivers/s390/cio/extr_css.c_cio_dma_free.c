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
 int /*<<< orphan*/  cio_dma_pool ; 
 int /*<<< orphan*/  cio_gp_dma_free (int /*<<< orphan*/ ,void*,size_t) ; 

void cio_dma_free(void *cpu_addr, size_t size)
{
	cio_gp_dma_free(cio_dma_pool, cpu_addr, size);
}