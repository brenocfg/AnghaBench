#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct soc_pcmcia_socket {int nr; } ;
struct sa1111_pcmcia_socket {TYPE_1__* dev; } ;
struct TYPE_5__ {int Vcc; int flags; } ;
typedef  TYPE_2__ socket_state_t ;
struct TYPE_4__ {scalar_t__ mapbase; } ;

/* Variables and functions */
 scalar_t__ PCCR ; 
 int PCCR_S0_FLT ; 
 int PCCR_S0_PSE ; 
 int PCCR_S0_PWAITEN ; 
 int PCCR_S0_RST ; 
 int PCCR_S1_FLT ; 
 int PCCR_S1_PSE ; 
 int PCCR_S1_PWAITEN ; 
 int PCCR_S1_RST ; 
 int SS_OUTPUT_ENA ; 
 int SS_RESET ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int readl_relaxed (scalar_t__) ; 
 struct sa1111_pcmcia_socket* to_skt (struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

int sa1111_pcmcia_configure_socket(struct soc_pcmcia_socket *skt, const socket_state_t *state)
{
	struct sa1111_pcmcia_socket *s = to_skt(skt);
	u32 pccr_skt_mask, pccr_set_mask, val;
	unsigned long flags;

	switch (skt->nr) {
	case 0:
		pccr_skt_mask = PCCR_S0_RST|PCCR_S0_FLT|PCCR_S0_PWAITEN|PCCR_S0_PSE;
		break;

	case 1:
		pccr_skt_mask = PCCR_S1_RST|PCCR_S1_FLT|PCCR_S1_PWAITEN|PCCR_S1_PSE;
		break;

	default:
		return -1;
	}

	pccr_set_mask = 0;

	if (state->Vcc != 0)
		pccr_set_mask |= PCCR_S0_PWAITEN|PCCR_S1_PWAITEN;
	if (state->Vcc == 50)
		pccr_set_mask |= PCCR_S0_PSE|PCCR_S1_PSE;
	if (state->flags & SS_RESET)
		pccr_set_mask |= PCCR_S0_RST|PCCR_S1_RST;
	if (state->flags & SS_OUTPUT_ENA)
		pccr_set_mask |= PCCR_S0_FLT|PCCR_S1_FLT;

	local_irq_save(flags);
	val = readl_relaxed(s->dev->mapbase + PCCR);
	val &= ~pccr_skt_mask;
	val |= pccr_set_mask & pccr_skt_mask;
	writel_relaxed(val, s->dev->mapbase + PCCR);
	local_irq_restore(flags);

	return 0;
}