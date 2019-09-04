#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cookie; } ;
struct ep93xx_dma_desc {TYPE_1__ txd; } ;
struct ep93xx_dma_chan {int /*<<< orphan*/  flags; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_DMA_IS_CYCLIC ; 
 struct ep93xx_dma_desc* ep93xx_dma_get_active (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  list_rotate_left (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ep93xx_dma_advance_active(struct ep93xx_dma_chan *edmac)
{
	struct ep93xx_dma_desc *desc;

	list_rotate_left(&edmac->active);

	if (test_bit(EP93XX_DMA_IS_CYCLIC, &edmac->flags))
		return true;

	desc = ep93xx_dma_get_active(edmac);
	if (!desc)
		return false;

	/*
	 * If txd.cookie is set it means that we are back in the first
	 * descriptor in the chain and hence done with it.
	 */
	return !desc->txd.cookie;
}