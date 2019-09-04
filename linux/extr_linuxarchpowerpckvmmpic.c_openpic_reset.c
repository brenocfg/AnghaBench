#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct openpic {int frr; int nb_irqs; int vid; int spve; int vector_mask; int max_irq; int ivpr_reset; scalar_t__ gcr; TYPE_3__* timers; TYPE_2__* dst; int /*<<< orphan*/  idr_reset; TYPE_1__* src; int /*<<< orphan*/  tfrr_reset; int /*<<< orphan*/  tfrr; scalar_t__ pir; } ;
struct irq_queue {int dummy; } ;
struct TYPE_8__ {int next; } ;
struct TYPE_7__ {int /*<<< orphan*/  tbcr; scalar_t__ tccr; } ;
struct TYPE_6__ {int ctpr; TYPE_4__ servicing; TYPE_4__ raised; } ;
struct TYPE_5__ {int ivpr; int type; int level; } ;

/* Variables and functions */
 int FRR_NIRQ_SHIFT ; 
 int FRR_VID_SHIFT ; 
 scalar_t__ GCR_RESET ; 
#define  IRQ_TYPE_FSLINT 130 
#define  IRQ_TYPE_FSLSPECIAL 129 
#define  IRQ_TYPE_NORMAL 128 
 int IVPR_POLARITY_MASK ; 
 int IVPR_SENSE_MASK ; 
 int MAX_CPU ; 
 int MAX_TMR ; 
 int /*<<< orphan*/  TBCR_CI ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_IRQreg_idr (struct openpic*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void openpic_reset(struct openpic *opp)
{
	int i;

	opp->gcr = GCR_RESET;
	/* Initialise controller registers */
	opp->frr = ((opp->nb_irqs - 1) << FRR_NIRQ_SHIFT) |
	    (opp->vid << FRR_VID_SHIFT);

	opp->pir = 0;
	opp->spve = -1 & opp->vector_mask;
	opp->tfrr = opp->tfrr_reset;
	/* Initialise IRQ sources */
	for (i = 0; i < opp->max_irq; i++) {
		opp->src[i].ivpr = opp->ivpr_reset;

		switch (opp->src[i].type) {
		case IRQ_TYPE_NORMAL:
			opp->src[i].level =
			    !!(opp->ivpr_reset & IVPR_SENSE_MASK);
			break;

		case IRQ_TYPE_FSLINT:
			opp->src[i].ivpr |= IVPR_POLARITY_MASK;
			break;

		case IRQ_TYPE_FSLSPECIAL:
			break;
		}

		write_IRQreg_idr(opp, i, opp->idr_reset);
	}
	/* Initialise IRQ destinations */
	for (i = 0; i < MAX_CPU; i++) {
		opp->dst[i].ctpr = 15;
		memset(&opp->dst[i].raised, 0, sizeof(struct irq_queue));
		opp->dst[i].raised.next = -1;
		memset(&opp->dst[i].servicing, 0, sizeof(struct irq_queue));
		opp->dst[i].servicing.next = -1;
	}
	/* Initialise timers */
	for (i = 0; i < MAX_TMR; i++) {
		opp->timers[i].tccr = 0;
		opp->timers[i].tbcr = TBCR_CI;
	}
	/* Go out of RESET state */
	opp->gcr = 0;
}