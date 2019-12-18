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
struct bgmac {scalar_t__ loopback; TYPE_1__* net_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGMAC_CMDCFG_ML ; 
 int /*<<< orphan*/  BGMAC_CMDCFG_RPI ; 
 int /*<<< orphan*/  BGMAC_INT_RECV_LAZY ; 
 int /*<<< orphan*/  BGMAC_INT_STATUS ; 
 int BGMAC_IRL_FC_SHIFT ; 
 int /*<<< orphan*/  BGMAC_RXMAX_LENGTH ; 
 int ETHER_MAX_LEN ; 
 int /*<<< orphan*/  bgmac_chip_intrs_on (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_cmdcfg_maskset (struct bgmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bgmac_enable (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_set_rx_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  bgmac_write (struct bgmac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bgmac_write_mac_address (struct bgmac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bgmac_chip_init(struct bgmac *bgmac)
{
	/* Clear any erroneously pending interrupts */
	bgmac_write(bgmac, BGMAC_INT_STATUS, ~0);

	/* 1 interrupt per received frame */
	bgmac_write(bgmac, BGMAC_INT_RECV_LAZY, 1 << BGMAC_IRL_FC_SHIFT);

	/* Enable 802.3x tx flow control (honor received PAUSE frames) */
	bgmac_cmdcfg_maskset(bgmac, ~BGMAC_CMDCFG_RPI, 0, true);

	bgmac_set_rx_mode(bgmac->net_dev);

	bgmac_write_mac_address(bgmac, bgmac->net_dev->dev_addr);

	if (bgmac->loopback)
		bgmac_cmdcfg_maskset(bgmac, ~0, BGMAC_CMDCFG_ML, false);
	else
		bgmac_cmdcfg_maskset(bgmac, ~BGMAC_CMDCFG_ML, 0, false);

	bgmac_write(bgmac, BGMAC_RXMAX_LENGTH, 32 + ETHER_MAX_LEN);

	bgmac_chip_intrs_on(bgmac);

	bgmac_enable(bgmac);
}