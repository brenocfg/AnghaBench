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
struct cppi_descriptor {int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct cppi_channel {struct cppi_descriptor* last_processed; struct cppi* controller; TYPE_1__ channel; } ;
struct cppi {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DMA_STATUS_UNKNOWN ; 
 struct cppi_descriptor* cppi_bd_alloc (struct cppi_channel*) ; 
 int /*<<< orphan*/  cppi_channel_abort (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct cppi_descriptor*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cppi_pool_free(struct cppi_channel *c)
{
	struct cppi		*cppi = c->controller;
	struct cppi_descriptor	*bd;

	(void) cppi_channel_abort(&c->channel);
	c->channel.status = MUSB_DMA_STATUS_UNKNOWN;
	c->controller = NULL;

	/* free all its bds */
	bd = c->last_processed;
	do {
		if (bd)
			dma_pool_free(cppi->pool, bd, bd->dma);
		bd = cppi_bd_alloc(c);
	} while (bd);
	c->last_processed = NULL;
}