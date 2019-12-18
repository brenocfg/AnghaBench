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
 int ENOMEM ; 
 int /*<<< orphan*/  cio_dma_pool ; 
 int /*<<< orphan*/  cio_get_dma_css_dev () ; 
 int /*<<< orphan*/  cio_gp_dma_create (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cio_dma_pool_init(void)
{
	/* No need to free up the resources: compiled in */
	cio_dma_pool = cio_gp_dma_create(cio_get_dma_css_dev(), 1);
	if (!cio_dma_pool)
		return -ENOMEM;
	return 0;
}