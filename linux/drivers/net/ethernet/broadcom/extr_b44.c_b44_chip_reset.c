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
typedef  int u32 ;
struct ssb_device {TYPE_1__* bus; } ;
struct b44 {int /*<<< orphan*/  flags; scalar_t__ rx_cons; scalar_t__ rx_prod; scalar_t__ tx_cons; scalar_t__ tx_prod; struct ssb_device* sdev; } ;
struct TYPE_2__ {int bustype; int /*<<< orphan*/  pcicore; } ;

/* Variables and functions */
 int B44_CHIP_RESET_PARTIAL ; 
 int /*<<< orphan*/  B44_DEVCTRL ; 
 int /*<<< orphan*/  B44_DMARX_CTRL ; 
 int /*<<< orphan*/  B44_DMARX_STAT ; 
 int /*<<< orphan*/  B44_DMATX_CTRL ; 
 int /*<<< orphan*/  B44_ENET_CTRL ; 
 int /*<<< orphan*/  B44_FLAG_EXTERNAL_PHY ; 
 int /*<<< orphan*/  B44_MDC_RATIO ; 
 int /*<<< orphan*/  B44_MDIO_CTRL ; 
 int /*<<< orphan*/  B44_RCV_LAZY ; 
 int DEVCTRL_EPR ; 
 int DEVCTRL_IPP ; 
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DMARX_STAT_EMASK ; 
 int DMARX_STAT_SIDLE ; 
 int ENET_CTRL_DISABLE ; 
 int ENET_CTRL_EPSEL ; 
 int MDIO_CTRL_MAXF_MASK ; 
 int MDIO_CTRL_PREAMBLE ; 
#define  SSB_BUSTYPE_PCI 131 
#define  SSB_BUSTYPE_PCMCIA 130 
#define  SSB_BUSTYPE_SDIO 129 
#define  SSB_BUSTYPE_SSB 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  b44_clear_stats (struct b44*) ; 
 int /*<<< orphan*/  b44_wait_bit (struct b44*,int /*<<< orphan*/ ,int,int,int) ; 
 int br32 (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssb_clockspeed (TYPE_1__*) ; 
 int /*<<< orphan*/  ssb_device_enable (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int ssb_device_is_enabled (struct ssb_device*) ; 
 int /*<<< orphan*/  ssb_pcicore_dev_irqvecs_enable (int /*<<< orphan*/ *,struct ssb_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b44_chip_reset(struct b44 *bp, int reset_kind)
{
	struct ssb_device *sdev = bp->sdev;
	bool was_enabled;

	was_enabled = ssb_device_is_enabled(bp->sdev);

	ssb_device_enable(bp->sdev, 0);
	ssb_pcicore_dev_irqvecs_enable(&sdev->bus->pcicore, sdev);

	if (was_enabled) {
		bw32(bp, B44_RCV_LAZY, 0);
		bw32(bp, B44_ENET_CTRL, ENET_CTRL_DISABLE);
		b44_wait_bit(bp, B44_ENET_CTRL, ENET_CTRL_DISABLE, 200, 1);
		bw32(bp, B44_DMATX_CTRL, 0);
		bp->tx_prod = bp->tx_cons = 0;
		if (br32(bp, B44_DMARX_STAT) & DMARX_STAT_EMASK) {
			b44_wait_bit(bp, B44_DMARX_STAT, DMARX_STAT_SIDLE,
				     100, 0);
		}
		bw32(bp, B44_DMARX_CTRL, 0);
		bp->rx_prod = bp->rx_cons = 0;
	}

	b44_clear_stats(bp);

	/*
	 * Don't enable PHY if we are doing a partial reset
	 * we are probably going to power down
	 */
	if (reset_kind == B44_CHIP_RESET_PARTIAL)
		return;

	switch (sdev->bus->bustype) {
	case SSB_BUSTYPE_SSB:
		bw32(bp, B44_MDIO_CTRL, (MDIO_CTRL_PREAMBLE |
		     (DIV_ROUND_CLOSEST(ssb_clockspeed(sdev->bus),
					B44_MDC_RATIO)
		     & MDIO_CTRL_MAXF_MASK)));
		break;
	case SSB_BUSTYPE_PCI:
		bw32(bp, B44_MDIO_CTRL, (MDIO_CTRL_PREAMBLE |
		     (0x0d & MDIO_CTRL_MAXF_MASK)));
		break;
	case SSB_BUSTYPE_PCMCIA:
	case SSB_BUSTYPE_SDIO:
		WARN_ON(1); /* A device with this bus does not exist. */
		break;
	}

	br32(bp, B44_MDIO_CTRL);

	if (!(br32(bp, B44_DEVCTRL) & DEVCTRL_IPP)) {
		bw32(bp, B44_ENET_CTRL, ENET_CTRL_EPSEL);
		br32(bp, B44_ENET_CTRL);
		bp->flags |= B44_FLAG_EXTERNAL_PHY;
	} else {
		u32 val = br32(bp, B44_DEVCTRL);

		if (val & DEVCTRL_EPR) {
			bw32(bp, B44_DEVCTRL, (val & ~DEVCTRL_EPR));
			br32(bp, B44_DEVCTRL);
			udelay(100);
		}
		bp->flags &= ~B44_FLAG_EXTERNAL_PHY;
	}
}