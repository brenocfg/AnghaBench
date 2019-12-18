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
struct TYPE_2__ {scalar_t__ pending; } ;
struct softing {TYPE_1__ tx; int /*<<< orphan*/ * dpram; } ;

/* Variables and functions */
 size_t DPRAM_RESET ; 
 size_t DPRAM_RESET_RX_FIFO ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int softing_fct_cmd (struct softing*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int softing_reset_chip(struct softing *card)
{
	int ret;

	do {
		/* reset chip */
		iowrite8(0, &card->dpram[DPRAM_RESET_RX_FIFO]);
		iowrite8(0, &card->dpram[DPRAM_RESET_RX_FIFO+1]);
		iowrite8(1, &card->dpram[DPRAM_RESET]);
		iowrite8(0, &card->dpram[DPRAM_RESET+1]);

		ret = softing_fct_cmd(card, 0, "reset_can");
		if (!ret)
			break;
		if (signal_pending(current))
			/* don't wait any longer */
			break;
	} while (1);
	card->tx.pending = 0;
	return ret;
}