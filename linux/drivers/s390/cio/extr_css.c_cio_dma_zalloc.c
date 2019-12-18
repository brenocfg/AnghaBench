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
 int /*<<< orphan*/  cio_get_dma_css_dev () ; 
 void* cio_gp_dma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void *cio_dma_zalloc(size_t size)
{
	return cio_gp_dma_zalloc(cio_dma_pool, cio_get_dma_css_dev(), size);
}