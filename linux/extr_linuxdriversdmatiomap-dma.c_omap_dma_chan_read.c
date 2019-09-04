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
struct omap_dma_reg {scalar_t__ offset; int /*<<< orphan*/  type; } ;
struct omap_chan {scalar_t__ channel_base; struct omap_dma_reg* reg_map; } ;

/* Variables and functions */
 int omap_dma_read (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static unsigned omap_dma_chan_read(struct omap_chan *c, unsigned reg)
{
	const struct omap_dma_reg *r = c->reg_map + reg;

	return omap_dma_read(r->type, c->channel_base + r->offset);
}