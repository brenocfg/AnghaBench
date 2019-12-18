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
struct soc_pcmcia_socket {size_t nr; TYPE_1__* stat; } ;
struct pcmcia_state {unsigned int bvd1; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 size_t SOC_STAT_BVD1 ; 
 size_t SOC_STAT_BVD2 ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 unsigned int* mst_pcmcia_bvd1_status ; 

__attribute__((used)) static void mst_pcmcia_socket_state(struct soc_pcmcia_socket *skt,
				    struct pcmcia_state *state)
{
	unsigned int flip = mst_pcmcia_bvd1_status[skt->nr] ^ state->bvd1;

	/*
	 * Workaround for STSCHG which can't be deasserted:
	 * We therefore disable/enable corresponding IRQs
	 * as needed to avoid IRQ locks.
	 */
	if (flip) {
		mst_pcmcia_bvd1_status[skt->nr] = state->bvd1;
		if (state->bvd1)
			enable_irq(skt->stat[SOC_STAT_BVD1].irq);
		else
			disable_irq(skt->stat[SOC_STAT_BVD2].irq);
	}
}