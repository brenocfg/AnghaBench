#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cookie; } ;
struct ppc440spe_adma_desc_slot {TYPE_1__ async_tx; } ;
struct ppc440spe_adma_chan {int dummy; } ;
typedef  scalar_t__ dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dma_descriptor_unmap (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_run_dependencies (TYPE_1__*) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback_invoke (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static dma_cookie_t ppc440spe_adma_run_tx_complete_actions(
		struct ppc440spe_adma_desc_slot *desc,
		struct ppc440spe_adma_chan *chan,
		dma_cookie_t cookie)
{
	BUG_ON(desc->async_tx.cookie < 0);
	if (desc->async_tx.cookie > 0) {
		cookie = desc->async_tx.cookie;
		desc->async_tx.cookie = 0;

		dma_descriptor_unmap(&desc->async_tx);
		/* call the callback (must not sleep or submit new
		 * operations to this channel)
		 */
		dmaengine_desc_get_callback_invoke(&desc->async_tx, NULL);
	}

	/* run dependent operations */
	dma_run_dependencies(&desc->async_tx);

	return cookie;
}