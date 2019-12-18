#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pl022 {int /*<<< orphan*/  virtbase; TYPE_3__* adev; TYPE_2__* cur_chip; TYPE_1__* cur_msg; int /*<<< orphan*/  cur_transfer; int /*<<< orphan*/  next_msg_cs_active; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ enable_dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int DISABLE_ALL_INTERRUPTS ; 
 int /*<<< orphan*/  EIO ; 
 int ENABLE_ALL_INTERRUPTS ; 
 int /*<<< orphan*/  SSP_CHIP_SELECT ; 
 int /*<<< orphan*/  SSP_CR1 (int /*<<< orphan*/ ) ; 
 int SSP_CR1_MASK_SSE ; 
 int /*<<< orphan*/  SSP_IMSC (int /*<<< orphan*/ ) ; 
 int SSP_IMSC_MASK_RXIM ; 
 int /*<<< orphan*/  STATE_ERROR ; 
 scalar_t__ configure_dma (struct pl022*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  giveback (struct pl022*) ; 
 int /*<<< orphan*/  pl022_cs_control (struct pl022*,int /*<<< orphan*/ ) ; 
 int readw (int /*<<< orphan*/ ) ; 
 scalar_t__ set_up_next_transfer (struct pl022*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_interrupt_dma_transfer(struct pl022 *pl022)
{
	/*
	 * Default is to enable all interrupts except RX -
	 * this will be enabled once TX is complete
	 */
	u32 irqflags = (u32)(ENABLE_ALL_INTERRUPTS & ~SSP_IMSC_MASK_RXIM);

	/* Enable target chip, if not already active */
	if (!pl022->next_msg_cs_active)
		pl022_cs_control(pl022, SSP_CHIP_SELECT);

	if (set_up_next_transfer(pl022, pl022->cur_transfer)) {
		/* Error path */
		pl022->cur_msg->state = STATE_ERROR;
		pl022->cur_msg->status = -EIO;
		giveback(pl022);
		return;
	}
	/* If we're using DMA, set up DMA here */
	if (pl022->cur_chip->enable_dma) {
		/* Configure DMA transfer */
		if (configure_dma(pl022)) {
			dev_dbg(&pl022->adev->dev,
				"configuration of DMA failed, fall back to interrupt mode\n");
			goto err_config_dma;
		}
		/* Disable interrupts in DMA mode, IRQ from DMA controller */
		irqflags = DISABLE_ALL_INTERRUPTS;
	}
err_config_dma:
	/* Enable SSP, turn on interrupts */
	writew((readw(SSP_CR1(pl022->virtbase)) | SSP_CR1_MASK_SSE),
	       SSP_CR1(pl022->virtbase));
	writew(irqflags, SSP_IMSC(pl022->virtbase));
}