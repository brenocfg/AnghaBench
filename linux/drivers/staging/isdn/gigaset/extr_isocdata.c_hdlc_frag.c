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
struct TYPE_6__ {TYPE_2__* bas; } ;
struct bc_state {int /*<<< orphan*/  rx_fcs; int /*<<< orphan*/  rx_skb; TYPE_3__ hw; TYPE_1__* cs; int /*<<< orphan*/  ignore; } ;
struct TYPE_5__ {int /*<<< orphan*/  alignerrs; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPP_INITFCS ; 
 int /*<<< orphan*/  __skb_trim (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  gigaset_isdn_rcv_err (struct bc_state*) ; 
 int /*<<< orphan*/  hdlc_flush (struct bc_state*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hdlc_frag(struct bc_state *bcs, unsigned inbits)
{
	if (unlikely(bcs->ignore)) {
		bcs->ignore--;
		hdlc_flush(bcs);
		return;
	}

	dev_notice(bcs->cs->dev, "received partial byte (%d bits)\n", inbits);
	bcs->hw.bas->alignerrs++;
	gigaset_isdn_rcv_err(bcs);
	__skb_trim(bcs->rx_skb, 0);
	bcs->rx_fcs = PPP_INITFCS;
}