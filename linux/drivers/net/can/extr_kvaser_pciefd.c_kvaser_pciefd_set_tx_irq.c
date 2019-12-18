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
typedef  int u32 ;
struct kvaser_pciefd_can {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ KVASER_PCIEFD_KCAN_IEN_REG ; 
 int KVASER_PCIEFD_KCAN_IRQ_ABD ; 
 int KVASER_PCIEFD_KCAN_IRQ_BPP ; 
 int KVASER_PCIEFD_KCAN_IRQ_FDIC ; 
 int KVASER_PCIEFD_KCAN_IRQ_ROF ; 
 int KVASER_PCIEFD_KCAN_IRQ_TAE ; 
 int KVASER_PCIEFD_KCAN_IRQ_TAL ; 
 int KVASER_PCIEFD_KCAN_IRQ_TAR ; 
 int KVASER_PCIEFD_KCAN_IRQ_TE ; 
 int KVASER_PCIEFD_KCAN_IRQ_TFD ; 
 int KVASER_PCIEFD_KCAN_IRQ_TOF ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static int kvaser_pciefd_set_tx_irq(struct kvaser_pciefd_can *can)
{
	u32 msk;

	msk = KVASER_PCIEFD_KCAN_IRQ_TE | KVASER_PCIEFD_KCAN_IRQ_ROF |
	      KVASER_PCIEFD_KCAN_IRQ_TOF | KVASER_PCIEFD_KCAN_IRQ_ABD |
	      KVASER_PCIEFD_KCAN_IRQ_TAE | KVASER_PCIEFD_KCAN_IRQ_TAL |
	      KVASER_PCIEFD_KCAN_IRQ_FDIC | KVASER_PCIEFD_KCAN_IRQ_BPP |
	      KVASER_PCIEFD_KCAN_IRQ_TAR | KVASER_PCIEFD_KCAN_IRQ_TFD;

	iowrite32(msk, can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);

	return 0;
}