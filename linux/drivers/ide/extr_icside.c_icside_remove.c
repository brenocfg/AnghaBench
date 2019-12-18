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
struct icside_state {int type; int /*<<< orphan*/  ioc_base; } ;
struct expansion_card {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
#define  ICS_TYPE_V5 129 
#define  ICS_TYPE_V6 128 
 int /*<<< orphan*/  NO_DMA ; 
 struct icside_state* ecard_get_drvdata (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_release_resources (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_set_drvdata (struct expansion_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icside_irqdisable_arcin_v5 (struct expansion_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icside_irqdisable_arcin_v6 (struct expansion_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct icside_state*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icside_remove(struct expansion_card *ec)
{
	struct icside_state *state = ecard_get_drvdata(ec);

	switch (state->type) {
	case ICS_TYPE_V5:
		/* FIXME: tell IDE to stop using the interface */

		/* Disable interrupts */
		icside_irqdisable_arcin_v5(ec, 0);
		break;

	case ICS_TYPE_V6:
		/* FIXME: tell IDE to stop using the interface */
		if (ec->dma != NO_DMA)
			free_dma(ec->dma);

		/* Disable interrupts */
		icside_irqdisable_arcin_v6(ec, 0);

		/* Reset the ROM pointer/EASI selection */
		writeb(0, state->ioc_base);
		break;
	}

	ecard_set_drvdata(ec, NULL);

	kfree(state);
	ecard_release_resources(ec);
}