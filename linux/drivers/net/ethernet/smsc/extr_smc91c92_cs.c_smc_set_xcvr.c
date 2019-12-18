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
typedef  int u_short ;
struct smc_private {int cfg; scalar_t__ manfid; scalar_t__ cardid; int media_status; } ;
struct net_device {unsigned int base_addr; scalar_t__ if_port; } ;

/* Variables and functions */
 scalar_t__ BANK_SELECT ; 
 int CFG_AUI_SELECT ; 
 scalar_t__ CONFIG ; 
 scalar_t__ MANFID_OSITECH ; 
 scalar_t__ OSITECH_AUI_PWR ; 
 int /*<<< orphan*/  OSI_AUI_PWR ; 
 scalar_t__ PRODID_OSITECH_SEVEN ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  mask_bits (int /*<<< orphan*/ ,scalar_t__) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  set_bits (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void smc_set_xcvr(struct net_device *dev, int if_port)
{
    struct smc_private *smc = netdev_priv(dev);
    unsigned int ioaddr = dev->base_addr;
    u_short saved_bank;

    saved_bank = inw(ioaddr + BANK_SELECT);
    SMC_SELECT_BANK(1);
    if (if_port == 2) {
	outw(smc->cfg | CFG_AUI_SELECT, ioaddr + CONFIG);
	if ((smc->manfid == MANFID_OSITECH) &&
	    (smc->cardid != PRODID_OSITECH_SEVEN))
	    set_bits(OSI_AUI_PWR, ioaddr - 0x10 + OSITECH_AUI_PWR);
	smc->media_status = ((dev->if_port == 0) ? 0x0001 : 0x0002);
    } else {
	outw(smc->cfg, ioaddr + CONFIG);
	if ((smc->manfid == MANFID_OSITECH) &&
	    (smc->cardid != PRODID_OSITECH_SEVEN))
	    mask_bits(~OSI_AUI_PWR, ioaddr - 0x10 + OSITECH_AUI_PWR);
	smc->media_status = ((dev->if_port == 0) ? 0x0012 : 0x4001);
    }
    SMC_SELECT_BANK(saved_bank);
}