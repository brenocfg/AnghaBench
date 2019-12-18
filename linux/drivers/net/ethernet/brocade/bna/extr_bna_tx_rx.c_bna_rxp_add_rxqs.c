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
struct bna_rxq {int dummy; } ;
struct TYPE_6__ {struct bna_rxq* hdr; struct bna_rxq* data; } ;
struct TYPE_5__ {struct bna_rxq* small; struct bna_rxq* large; } ;
struct TYPE_7__ {int /*<<< orphan*/ * reserved; struct bna_rxq* only; } ;
struct TYPE_8__ {TYPE_2__ hds; TYPE_1__ slr; TYPE_3__ single; } ;
struct bna_rxp {int type; TYPE_4__ rxq; } ;

/* Variables and functions */
#define  BNA_RXP_HDS 130 
#define  BNA_RXP_SINGLE 129 
#define  BNA_RXP_SLR 128 

__attribute__((used)) static void
bna_rxp_add_rxqs(struct bna_rxp *rxp, struct bna_rxq *q0,
		struct bna_rxq *q1)
{
	switch (rxp->type) {
	case BNA_RXP_SINGLE:
		rxp->rxq.single.only = q0;
		rxp->rxq.single.reserved = NULL;
		break;
	case BNA_RXP_SLR:
		rxp->rxq.slr.large = q0;
		rxp->rxq.slr.small = q1;
		break;
	case BNA_RXP_HDS:
		rxp->rxq.hds.data = q0;
		rxp->rxq.hds.hdr = q1;
		break;
	default:
		break;
	}
}