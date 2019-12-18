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
struct sh_eth_private {int irq_enabled; TYPE_1__* cd; scalar_t__ duplex; } ;
struct net_device {int mtu; int features; } ;
struct TYPE_2__ {int (* soft_reset ) (struct net_device*) ;int fdr_value; int trscer_err_mask; int fcftr_value; int eesipr_value; int ecsr_value; int ecsipr_value; scalar_t__ tpauser; scalar_t__ mpr; scalar_t__ apr; int /*<<< orphan*/  (* set_rate ) (struct net_device*) ;int /*<<< orphan*/  no_trimd; scalar_t__ bculr; scalar_t__ nbst; scalar_t__ hw_swap; scalar_t__ rpadir; scalar_t__ rmiimode; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR ; 
 int /*<<< orphan*/  BCULR ; 
 int /*<<< orphan*/  ECMR ; 
 int ECMR_DM ; 
 int ECMR_RCSC ; 
 int ECMR_RE ; 
 int ECMR_TE ; 
 int ECMR_ZPF ; 
 int /*<<< orphan*/  ECSIPR ; 
 int /*<<< orphan*/  ECSR ; 
 int /*<<< orphan*/  EDMR ; 
 int EDMR_EL ; 
 int /*<<< orphan*/  EDMR_NBST ; 
 int /*<<< orphan*/  EDRRR ; 
 int EDRRR_R ; 
 int /*<<< orphan*/  EESIPR ; 
 int /*<<< orphan*/  EESR ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  FCFTR ; 
 int /*<<< orphan*/  FDR ; 
 int /*<<< orphan*/  MPR ; 
 int NETIF_F_RXCSUM ; 
 int NET_IP_ALIGN ; 
 int /*<<< orphan*/  RFLR ; 
 int /*<<< orphan*/  RMCR ; 
 int RMCR_RNC ; 
 int /*<<< orphan*/  RMIIMODE ; 
 int /*<<< orphan*/  RPADIR ; 
 int /*<<< orphan*/  TFTR ; 
 int /*<<< orphan*/  TPAUSER ; 
 int TPAUSER_UNLIMITED ; 
 int /*<<< orphan*/  TRIMD ; 
 int /*<<< orphan*/  TRSCER ; 
 int VLAN_HLEN ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_ring_format (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_write (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 
 int /*<<< orphan*/  update_mac_address (struct net_device*) ; 

__attribute__((used)) static int sh_eth_dev_init(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	int ret;

	/* Soft Reset */
	ret = mdp->cd->soft_reset(ndev);
	if (ret)
		return ret;

	if (mdp->cd->rmiimode)
		sh_eth_write(ndev, 0x1, RMIIMODE);

	/* Descriptor format */
	sh_eth_ring_format(ndev);
	if (mdp->cd->rpadir)
		sh_eth_write(ndev, NET_IP_ALIGN << 16, RPADIR);

	/* all sh_eth int mask */
	sh_eth_write(ndev, 0, EESIPR);

#if defined(__LITTLE_ENDIAN)
	if (mdp->cd->hw_swap)
		sh_eth_write(ndev, EDMR_EL, EDMR);
	else
#endif
		sh_eth_write(ndev, 0, EDMR);

	/* FIFO size set */
	sh_eth_write(ndev, mdp->cd->fdr_value, FDR);
	sh_eth_write(ndev, 0, TFTR);

	/* Frame recv control (enable multiple-packets per rx irq) */
	sh_eth_write(ndev, RMCR_RNC, RMCR);

	sh_eth_write(ndev, mdp->cd->trscer_err_mask, TRSCER);

	/* DMA transfer burst mode */
	if (mdp->cd->nbst)
		sh_eth_modify(ndev, EDMR, EDMR_NBST, EDMR_NBST);

	/* Burst cycle count upper-limit */
	if (mdp->cd->bculr)
		sh_eth_write(ndev, 0x800, BCULR);

	sh_eth_write(ndev, mdp->cd->fcftr_value, FCFTR);

	if (!mdp->cd->no_trimd)
		sh_eth_write(ndev, 0, TRIMD);

	/* Recv frame limit set register */
	sh_eth_write(ndev, ndev->mtu + ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN,
		     RFLR);

	sh_eth_modify(ndev, EESR, 0, 0);
	mdp->irq_enabled = true;
	sh_eth_write(ndev, mdp->cd->eesipr_value, EESIPR);

	/* EMAC Mode: PAUSE prohibition; Duplex; RX Checksum; TX; RX */
	sh_eth_write(ndev, ECMR_ZPF | (mdp->duplex ? ECMR_DM : 0) |
		     (ndev->features & NETIF_F_RXCSUM ? ECMR_RCSC : 0) |
		     ECMR_TE | ECMR_RE, ECMR);

	if (mdp->cd->set_rate)
		mdp->cd->set_rate(ndev);

	/* E-MAC Status Register clear */
	sh_eth_write(ndev, mdp->cd->ecsr_value, ECSR);

	/* E-MAC Interrupt Enable register */
	sh_eth_write(ndev, mdp->cd->ecsipr_value, ECSIPR);

	/* Set MAC address */
	update_mac_address(ndev);

	/* mask reset */
	if (mdp->cd->apr)
		sh_eth_write(ndev, 1, APR);
	if (mdp->cd->mpr)
		sh_eth_write(ndev, 1, MPR);
	if (mdp->cd->tpauser)
		sh_eth_write(ndev, TPAUSER_UNLIMITED, TPAUSER);

	/* Setting the Rx mode will start the Rx process. */
	sh_eth_write(ndev, EDRRR_R, EDRRR);

	return ret;
}