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
struct omap_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR ; 
 scalar_t__ dma_omap1 () ; 
 int /*<<< orphan*/  omap_dma_chan_read (struct omap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dma_chan_write (struct omap_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_dma_clear_csr(struct omap_chan *c)
{
	if (dma_omap1())
		omap_dma_chan_read(c, CSR);
	else
		omap_dma_chan_write(c, CSR, ~0);
}