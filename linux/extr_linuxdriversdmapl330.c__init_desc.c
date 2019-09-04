#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tx_submit; } ;
struct TYPE_3__ {void* dcctl; void* scctl; int /*<<< orphan*/  swap; } ;
struct dma_pl330_desc {int /*<<< orphan*/  node; TYPE_2__ txd; TYPE_1__ rqcfg; } ;

/* Variables and functions */
 void* CCTRL0 ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SWAP_NO ; 
 int /*<<< orphan*/  pl330_tx_submit ; 

__attribute__((used)) static inline void _init_desc(struct dma_pl330_desc *desc)
{
	desc->rqcfg.swap = SWAP_NO;
	desc->rqcfg.scctl = CCTRL0;
	desc->rqcfg.dcctl = CCTRL0;
	desc->txd.tx_submit = pl330_tx_submit;

	INIT_LIST_HEAD(&desc->node);
}