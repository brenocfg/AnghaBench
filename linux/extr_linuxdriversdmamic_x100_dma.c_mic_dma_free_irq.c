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
struct mic_dma_chan {int /*<<< orphan*/  cookie; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_irq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mic_dma_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mic_dma_chan*) ; 
 int /*<<< orphan*/  to_mbus_device (struct mic_dma_chan*) ; 
 TYPE_1__* to_mbus_hw_ops (struct mic_dma_chan*) ; 

__attribute__((used)) static inline void mic_dma_free_irq(struct mic_dma_chan *ch)
{
	to_mbus_hw_ops(ch)->free_irq(to_mbus_device(ch), ch->cookie, ch);
}