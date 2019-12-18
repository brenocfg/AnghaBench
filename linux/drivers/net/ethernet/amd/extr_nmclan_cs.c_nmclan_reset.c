#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pcmcia_device {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_5__ {void* tx_free_frames; struct pcmcia_device link; } ;
typedef  TYPE_1__ mace_private ;

/* Variables and functions */
 void* AM2150_MAX_TX_FRAMES ; 
 int /*<<< orphan*/  CISREG_COR ; 
 int COR_CONFIG_MASK ; 
 int COR_LEVEL_REQ ; 
 int COR_SOFT_RESET ; 
 int /*<<< orphan*/  MACE_IMR ; 
 int /*<<< orphan*/  MACE_IMR_DEFAULT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mace_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mace_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_read_config_byte (struct pcmcia_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcmcia_write_config_byte (struct pcmcia_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  restore_multicast_list (struct net_device*) ; 

__attribute__((used)) static void nmclan_reset(struct net_device *dev)
{
  mace_private *lp = netdev_priv(dev);

#if RESET_XILINX
  struct pcmcia_device *link = &lp->link;
  u8 OrigCorValue;

  /* Save original COR value */
  pcmcia_read_config_byte(link, CISREG_COR, &OrigCorValue);

  /* Reset Xilinx */
  dev_dbg(&link->dev, "nmclan_reset: OrigCorValue=0x%x, resetting...\n",
	OrigCorValue);
  pcmcia_write_config_byte(link, CISREG_COR, COR_SOFT_RESET);
  /* Need to wait for 20 ms for PCMCIA to finish reset. */

  /* Restore original COR configuration index */
  pcmcia_write_config_byte(link, CISREG_COR,
			  (COR_LEVEL_REQ | (OrigCorValue & COR_CONFIG_MASK)));
  /* Xilinx is now completely reset along with the MACE chip. */
  lp->tx_free_frames=AM2150_MAX_TX_FRAMES;

#endif /* #if RESET_XILINX */

  /* Xilinx is now completely reset along with the MACE chip. */
  lp->tx_free_frames=AM2150_MAX_TX_FRAMES;

  /* Reinitialize the MACE chip for operation. */
  mace_init(lp, dev->base_addr, dev->dev_addr);
  mace_write(lp, dev->base_addr, MACE_IMR, MACE_IMR_DEFAULT);

  /* Restore the multicast list and enable TX and RX. */
  restore_multicast_list(dev);
}